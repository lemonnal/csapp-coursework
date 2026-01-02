// 互斥锁示例
// 演示如何使用互斥锁保护共享资源

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define INCREMENTS 100000

// 共享变量
int counter = 0;

// 互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 不安全的递增函数
void *unsafe_increment(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        counter++;  // 竞态条件!
    }
    return NULL;
}

// 安全的递增函数
void *safe_increment(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void test_without_mutex() {
    printf("=== 无互斥锁保护 ===\n");

    counter = 0;
    pthread_t threads[NUM_THREADS];

    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, unsafe_increment, NULL);
    }

    // 等待线程
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("预期值: %d\n", NUM_THREADS * INCREMENTS);
    printf("实际值: %d\n", counter);
    printf("差异: %d\n\n", NUM_THREADS * INCREMENTS - counter);
}

void test_with_mutex() {
    printf("=== 有互斥锁保护 ===\n");

    counter = 0;
    pthread_t threads[NUM_THREADS];

    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, safe_increment, NULL);
    }

    // 等待线程
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("预期值: %d\n", NUM_THREADS * INCREMENTS);
    printf("实际值: %d\n", counter);
    printf("差异: %d\n", NUM_THREADS * INCREMENTS - counter);
}

int main() {
    test_without_mutex();
    test_with_mutex();

    pthread_mutex_destroy(&mutex);

    return 0;
}

// 编译命令:
// gcc -pthread mutex_demo.c -o mutex_demo
