# 第12章 并发编程

## 核心概念

### 并发基础
- **并发**: 多个任务在同一时间段内进行
- **并行**: 多个任务在同一时刻执行
- **进程**: 独立的资源单位
- **线程**: 调度的基本单位

### 并发类型
- **应用级并发**: 多个应用同时运行
- **进程级并发**: 多个进程共享系统资源
- **线程级并发**: 同一进程内多个线程

### 并发挑战
- **竞态条件**: 结果依赖于执行顺序
- **死锁**: 多个线程互相等待
- **饥饿**: 线程无法获得所需资源
- **活锁**: 线程不断改变状态但无法推进

## 难点解析

### 线程
- **创建**: pthread_create()
- **终止**: pthread_exit()
- **等待**: pthread_join()
- **分离**: pthread_detach()

### 同步机制
- **互斥锁(Mutex)**: 保护共享资源
- **条件变量**: 线程间通信
- **信号量**: 计数同步
- **读写锁**: 多读者单写者

### 线程安全
- **可重入函数**: 多线程安全调用
- **线程安全函数**: 使用同步机制
- **竞态条件**: 未保护的共享变量

### 死锁
- **必要条件**: 互斥、占有并等待、非抢占、循环等待
- **预防**: 打破其中一个条件
- **避免**: 银行家算法
- **检测**: 资源分配图

## 实践联系

### 线程创建示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS 4

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d is running\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[THREADS];
    int thread_ids[THREADS];

    // 创建线程
    for (int i = 0; i < THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    // 等待线程完成
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed\n");
    return 0;
}
```

### 互斥锁示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];

    // 创建线程
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // 等待线程完成
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Counter value: %d\n", counter);

    pthread_mutex_destroy(&mutex);
    return 0;
}
```

### 生产者-消费者模型
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define PRODUCER_LOOPS 10
#define CONSUMER_LOOPS 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < PRODUCER_LOOPS; i++) {
        pthread_mutex_lock(&mutex);

        // 等待缓冲区有空间
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }

        // 生产数据
        buffer[count++] = i;
        printf("Produced: %d (count=%d)\n", i, count);

        // 通知消费者
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < CONSUMER_LOOPS; i++) {
        pthread_mutex_lock(&mutex);

        // 等待缓冲区有数据
        while (count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        // 消费数据
        int item = buffer[--count];
        printf("Consumed: %d (count=%d)\n", item, count);

        // 通知生产者
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}
```

### 读写锁示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared_data = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *reader(void *arg) {
    int id = *(int *)arg;

    pthread_rwlock_rdlock(&rwlock);
    printf("Reader %d: read data = %d\n", id, shared_data);
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    pthread_rwlock_wrlock(&rwlock);
    shared_data++;
    printf("Writer %d: wrote data = %d\n", id, shared_data);
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

int main() {
    pthread_t threads[10];
    int ids[10];

    // 创建读者和写者线程
    for (int i = 0; i < 10; i++) {
        ids[i] = i;
        if (i % 3 == 0) {
            pthread_create(&threads[i], NULL, writer, &ids[i]);
        } else {
            pthread_create(&threads[i], NULL, reader, &ids[i]);
        }
    }

    // 等待所有线程完成
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
```

## 同步原语对比

| 同步机制 | 用途 | 特点 |
|---------|------|------|
| 互斥锁 | 保护临界区 | 简单高效 |
| 条件变量 | 线程间通信 | 需配合互斥锁 |
| 信号量 | 计数同步 | 可用于进程间 |
| 读写锁 | 多读者单写者 | 提高并发度 |

## 性能考虑
- **锁粒度**: 细粒度锁提高并发
- **锁竞争**: 减少锁持有时间
- **无锁编程**: 使用原子操作
- **线程池**: 重用线程资源

## 调试工具
```bash
# 检测线程错误
gcc -pthread -g program.c -o program
valgrind --tool=helgrind ./program

# 检测死锁
valgrind --tool=drd ./program

# 查看线程信息
ps -T -p <pid>
top -H -p <pid>
```

## 常见陷阱
- **忘记解锁**: 使用pthread_cleanup_push
- **锁的顺序**: 避免死锁
- **虚假唤醒**: 在循环中使用条件变量
- **信号丢失**: 及时发送信号

## 思考问题

1. 如何避免死锁?
2. 互斥锁和信号量的区别?
3. 如何实现线程安全的数据结构?

## 延伸阅读

- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [The Art of Multiprocessor Programming](https://www.elsevier.com/books/the-art-of-multiprocessor-programming/herlihy/978-0-12-370591-4)
- [Concurrency in Go](https://www.oreilly.com/library/view/concurrency-in-go/9781491941194/)
