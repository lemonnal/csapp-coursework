// 简单的内存分配跟踪工具
// 用于检测内存泄漏

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 内存分配记录
typedef struct Allocation {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct Allocation *next;
} Allocation;

// 全局链表头
static Allocation *allocations = NULL;
static size_t total_allocated = 0;
static size_t allocation_count = 0;

// 记录分配
void *tracked_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "内存分配失败: %s:%d\n", file, line);
        return NULL;
    }

    // 创建记录
    Allocation *record = (Allocation *)malloc(sizeof(Allocation));
    if (record == NULL) {
        free(ptr);
        return NULL;
    }

    record->ptr = ptr;
    record->size = size;
    record->file = file;
    record->line = line;
    record->next = allocations;
    allocations = record;

    total_allocated += size;
    allocation_count++;

    printf("分配: %p (%zu bytes) at %s:%d\n", ptr, size, file, line);
    return ptr;
}

// 记录释放
void tracked_free(void *ptr, const char *file, int line) {
    if (ptr == NULL) {
        return;
    }

    Allocation **current = &allocations;
    while (*current != NULL) {
        if ((*current)->ptr == ptr) {
            Allocation *to_remove = *current;
            *current = (*current)->next;

            total_allocated -= to_remove->size;
            allocation_count--;

            printf("释放: %p (%zu bytes) at %s:%d\n",
                   ptr, to_remove->size, file, line);

            free(to_remove);
            free(ptr);
            return;
        }
        current = &(*current)->next;
    }

    fprintf(stderr, "警告: 试图释放未分配的内存: %p at %s:%d\n",
            ptr, file, line);
    free(ptr);
}

// 检查内存泄漏
void check_memory_leaks() {
    printf("\n=== 内存泄漏报告 ===\n");
    printf("总分配次数: %zu\n", allocation_count);
    printf("当前分配内存: %zu bytes\n", total_allocated);

    if (allocations != NULL) {
        printf("\n未释放的内存:\n");
        Allocation *current = allocations;
        while (current != NULL) {
            printf("  %p (%zu bytes) 分配于 %s:%d\n",
                   current->ptr, current->size,
                   current->file, current->line);
            current = current->next;
        }
    } else {
        printf("没有内存泄漏!\n");
    }
    printf("===================\n");
}

// 定义便捷宏
#define MALLOC(size) tracked_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) tracked_free(ptr, __FILE__, __LINE__)

// 测试代码
void test_no_leak() {
    int *arr = MALLOC(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    FREE(arr);
}

void test_leak() {
    char *str = MALLOC(100);
    strcpy(str, "This will leak!");
    // 忘记释放,故意制造泄漏
}

void test_double_free() {
    int *x = MALLOC(sizeof(int));
    *x = 42;
    FREE(x);
    FREE(x);  // 双重释放
}

int main() {
    printf("=== 内存跟踪测试 ===\n\n");

    test_no_leak();
    test_leak();
    test_double_free();

    check_memory_leaks();

    return 0;
}

// 编译:
// gcc memory_trace.c -o memory_trace
//
// 使用 Valgrind 进行更专业的检测:
// valgrind --leak-check=full --show-leak-kinds=all ./memory_trace
