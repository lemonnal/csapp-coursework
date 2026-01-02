// 函数调用与栈帧示例
// 演示函数调用时的栈变化

#include <stdio.h>

// 简单的递归函数
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 多参数函数
int sum_five(int a, int b, int c, int d, int e) {
    return a + b + c + d + e;
}

// 调用示例
int main() {
    printf("5! = %d\n", factorial(5));

    int result = sum_five(1, 2, 3, 4, 5);
    printf("Sum = %d\n", result);

    return 0;
}

/*
 * 查看栈帧布局:
 * gcc -g -O0 call_stack.c -o call_stack
 * gdb ./call_stack
 * (gdb) break main
 * (gdb) run
 * (gdb) info frame
 * (gdb) x/20x $rsp
 */
