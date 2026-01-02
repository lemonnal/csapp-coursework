// 缓冲区溢出检测工具
// 演示常见的缓冲区溢出问题

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 演示1: 简单的缓冲区溢出
void demo_simple_overflow() {
    printf("=== 演示1: 简单缓冲区溢出 ===\n");

    char buffer[10];
    strcpy(buffer, "This string is too long for the buffer!");

    printf("Buffer content: %s\n", buffer);
    printf("注意: 这可能导致段错误或安全漏洞!\n\n");
}

// 演示2: 安全的字符串操作
void demo_safe_string_handling() {
    printf("=== 演示2: 安全的字符串操作 ===\n");

    char buffer[10];
    const char *long_string = "This is a long string";

    // 使用 strncpy 限制复制长度
    strncpy(buffer, long_string, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // 确保以 null 结尾

    printf("Safe buffer content: %s\n", buffer);
    printf("Truncated but safe!\n\n");
}

// 演示3: 栈破坏
void demo_stack_smashing() {
    printf("=== 演示3: 栈破坏检测 ===\n");

    char buffer[8];
    int value = 12345;

    printf("Before overflow: value = %d\n", value);

    // 这个溢出会覆盖栈上的其他变量
    memset(buffer, 'A', 20);

    printf("After overflow: value = %d\n", value);
    printf("注意: 现代编译器有栈保护机制!\n\n");
}

// 演示4: 使用安全的函数
void demo_secure_functions() {
    printf("=== 演示4: 使用安全的函数 ===\n");

    char dest[10];
    const char *src = "Hello, World!";

    // 不安全: 可能溢出
    // strcpy(dest, src);

    // 安全版本1: strncpy
    strncpy(dest, src, sizeof(dest) - 1);
    dest[sizeof(dest) - 1] = '\0';
    printf("strncpy: %s\n", dest);

    // 安全版本2: snprintf
    snprintf(dest, sizeof(dest), "%s", src);
    printf("snprintf: %s\n", dest);

    printf("\n建议: 始终使用安全的字符串函数!\n\n");
}

// 演示5: 动态内存分配
void demo_dynamic_allocation() {
    printf("=== 演示5: 动态内存分配 ===\n");

    const char *large_data = "This is a very long string that might overflow a stack buffer";

    // 分配足够的内存
    char *buffer = (char *)malloc(strlen(large_data) + 1);
    if (buffer == NULL) {
        printf("内存分配失败!\n");
        return;
    }

    strcpy(buffer, large_data);
    printf("Dynamic buffer: %s\n", buffer);

    free(buffer);
    printf("内存已释放\n\n");
}

int main() {
    printf("=== 缓冲区溢出演示工具 ===\n");
    printf("警告: 某些演示可能导致程序崩溃!\n\n");

    // 这些演示可能危险,注释掉不安全的代码
    // demo_simple_overflow();
    // demo_stack_smashing();

    demo_safe_string_handling();
    demo_secure_functions();
    demo_dynamic_allocation();

    printf("=== 防御建议 ===\n");
    printf("1. 使用安全的字符串函数 (strncpy, snprintf等)\n");
    printf("2. 始终检查边界\n");
    printf("3. 使用编译器保护选项 (-fstack-protector)\n");
    printf("4. 使用静态分析工具检测漏洞\n");
    printf("5. 使用动态内存分配处理大数据\n");

    return 0;
}
