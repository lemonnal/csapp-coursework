// 线程基础示例
// 演示线程的创建和基本使用

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// 线程函数
void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    printf("线程 %d: 正在运行\n", thread_id);

    // 模拟工作
    for (int i = 0; i < 3; i++) {
        printf("线程 %d: 工作中... %d\n", thread_id, i);
        sleep(1);
    }

    printf("线程 %d: 完成\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("=== 线程创建示例 ===\n\n");

    // 创建多个线程
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);

        if (result != 0) {
            perror("线程创建失败");
            return 1;
        }

        printf("主线程: 创建了线程 %d\n", i);
    }

    // 等待所有线程完成
    printf("\n主线程: 等待所有线程完成...\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n主线程: 所有线程已完成\n");

    return 0;
}

// 编译命令:
// gcc -pthread thread_demo.c -o thread_demo
