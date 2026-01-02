// 内存布局示例
// 演示程序的内存分布

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 全局变量(已初始化数据段)
int global_initialized = 100;

// 全局变量(未初始化数据段/bss)
int global_uninitialized;

// 字符串常量(只读数据段)
const char *message = "Hello, Memory!";

void print_memory_info() {
    // 栈变量
    int stack_var = 10;

    // 堆变量
    int *heap_var = (int *)malloc(sizeof(int));
    *heap_var = 20;

    printf("=== 内存布局示例 ===\n\n");

    // 打印各区域的地址
    printf("代码段:     %p\n", (void *)print_memory_info);
    printf("只读数据:    %p\n", (void *)message);
    printf("全局变量(已初始化): %p\n", (void *)&global_initialized);
    printf("全局变量(未初始化): %p\n", (void *)&global_uninitialized);
    printf("堆变量:     %p\n", (void *)heap_var);
    printf("栈变量:     %p\n", (void *)&stack_var);

    printf("\n=== 内存布局(从低到高) ===\n");
    printf("1. 代码段(只读)\n");
    printf("2. 只读数据段(.rodata)\n");
    printf("3. 已初始化数据段(.data)\n");
    printf("4. 未初始化数据段(.bss)\n");
    printf("5. 堆(向上增长)\n");
    printf("6. 栈(向下增长)\n");
    printf("7. 命令行参数和环境变量\n");

    free(heap_var);
}

int main() {
    print_memory_info();
    return 0;
}
