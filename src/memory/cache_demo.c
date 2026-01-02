// 缓存友好代码示例
// 演示如何编写缓存友好的代码

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024

// 缓存不友好的矩阵访问(按列访问)
void cache_unfriendly(int **matrix, int n) {
    clock_t start = clock();

    int sum = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            sum += matrix[i][j];  // 跳跃访问,空间局部性差
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("缓存不友好: sum = %d, time = %.4f seconds\n", sum, time_spent);
}

// 缓存友好的矩阵访问(按行访问)
void cache_friendly(int **matrix, int n) {
    clock_t start = clock();

    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j];  // 连续访问,空间局部性好
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("缓存友好:   sum = %d, time = %.4f seconds\n", sum, time_spent);
}

// 分块矩阵访问
void cache_blocked(int **matrix, int n) {
    clock_t start = clock();

    int sum = 0;
    int block_size = 16;  // 根据缓存大小调整

    for (int ii = 0; ii < n; ii += block_size) {
        for (int jj = 0; jj < n; jj += block_size) {
            // 处理一个块
            for (int i = ii; i < ii + block_size && i < n; i++) {
                for (int j = jj; j < jj + block_size && j < n; j++) {
                    sum += matrix[i][j];
                }
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("分块访问:   sum = %d, time = %.4f seconds\n", sum, time_spent);
}

int main() {
    int n = SIZE;

    // 分配矩阵
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i + j;
        }
    }

    printf("矩阵大小: %d x %d\n\n", n, n);

    // 测试不同访问模式
    cache_friendly(matrix, n);
    cache_unfriendly(matrix, n);
    cache_blocked(matrix, n);

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
