// 生产者-消费者模型示例
// 使用条件变量实现线程间同步

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCER_COUNT 2
#define CONSUMER_COUNT 2
#define PRODUCER_LOOPS 5
#define CONSUMER_LOOPS 5

// 共享缓冲区
int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

// 同步原语
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;

// 生产者函数
void *producer(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < PRODUCER_LOOPS; i++) {
        int item = id * 100 + i;

        pthread_mutex_lock(&mutex);

        // 等待缓冲区有空间
        while (count == BUFFER_SIZE) {
            printf("生产者 %d: 缓冲区已满,等待...\n", id);
            pthread_cond_wait(&cond_not_full, &mutex);
        }

        // 生产数据
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("生产者 %d: 生产了 %d (缓冲区: %d/%d)\n",
               id, item, count, BUFFER_SIZE);

        // 通知消费者
        pthread_cond_signal(&cond_not_empty);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    printf("生产者 %d: 完成\n", id);
    return NULL;
}

// 消费者函数
void *consumer(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < CONSUMER_LOOPS; i++) {
        pthread_mutex_lock(&mutex);

        // 等待缓冲区有数据
        while (count == 0) {
            printf("消费者 %d: 缓冲区为空,等待...\n", id);
            pthread_cond_wait(&cond_not_empty, &mutex);
        }

        // 消费数据
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("消费者 %d: 消费了 %d (缓冲区: %d/%d)\n",
               id, item, count, BUFFER_SIZE);

        // 通知生产者
        pthread_cond_signal(&cond_not_full);
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }

    printf("消费者 %d: 完成\n", id);
    return NULL;
}

int main() {
    pthread_t producers[PRODUCER_COUNT];
    pthread_t consumers[CONSUMER_COUNT];
    int producer_ids[PRODUCER_COUNT];
    int consumer_ids[CONSUMER_COUNT];

    printf("=== 生产者-消费者模型 ===\n\n");

    // 创建生产者线程
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // 创建消费者线程
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // 等待所有线程完成
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(consumers[i], NULL);
    }

    printf("\n所有线程已完成\n");

    // 清理资源
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_not_full);
    pthread_cond_destroy(&cond_not_empty);

    return 0;
}

// 编译命令:
// gcc -pthread producer_consumer.c -o producer_consumer
