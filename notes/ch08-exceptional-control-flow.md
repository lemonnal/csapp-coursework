# 第8章 异常控制流

## 核心概念

### 异常控制流(ECF)
- **异常**: 系统对事件发生的响应
- **中断**: 外部设备产生的异步事件
- **陷阱**: 有意的异常(系统调用)
- **故障**: 由错误引起的可恢复异常
- **终止**: 不可恢复的错误

### 进程控制
- **进程**: 运行中的程序实例
- **进程ID**: 每个进程的唯一标识
- **进程状态**: 运行、停止、终止
- **进程上下文**: 程序计数器、寄存器、内存等

### 信号
- **信号类型**: SIGINT, SIGKILL, SIGSTOP, SIGCONT等
- **信号处理**: 默认、忽略、捕获
- **信号发送**: kill, raise, alarm

## 难点解析

### 异常处理流程
1. 事件发生
2. 处理器检测到异常
3. 保存上下文
4. 调用异常处理程序
5. 恢复上下文
6. 返回或终止

### 进程创建
- **fork()**: 创建子进程
- **exec()**: 加载新程序
- **wait()**: 等待子进程
- **exit()**: 终止进程

### 进程控制块(PCB)
- 进程状态信息
- 程序计数器
- 寄存器内容
- 调度信息
- 内存管理信息

### 信号处理机制
- **信号集**: 阻塞和未决信号
- **信号掩码**: 阻塞的信号集合
- **信号处理函数**: 自定义处理逻辑

## 实践联系

### Shell Lab 关联
- 进程创建和终止
- 信号处理
- 作业控制
- 前台/后台进程

### 进程控制示例
```c
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // 子进程
        printf("Child process (PID=%d)\n", getpid());
        _exit(0);
    } else if (pid > 0) {
        // 父进程
        printf("Parent process (PID=%d)\n", getpid());
        wait(NULL);  // 等待子进程
    } else {
        // fork失败
        perror("fork failed");
    }

    return 0;
}
```

### 信号处理示例
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigint_handler(int sig) {
    printf("Received SIGINT (Ctrl+C)\n");
    _exit(0);
}

int main() {
    // 注册信号处理函数
    signal(SIGINT, sigint_handler);

    printf("Running... Press Ctrl+C\n");
    while (1) {
        sleep(1);
    }

    return 0;
}
```

### 信号量示例
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int sig) {
    printf("Alarm!\n");
}

int main() {
    signal(SIGALRM, alarm_handler);
    alarm(3);  // 3秒后发送SIGALRM

    printf("Waiting for alarm...\n");
    pause();  // 等待信号

    return 0;
}
```

## 系统调用
- **fork()**: 创建子进程
- **exit()**: 终止进程
- **wait()**: 等待子进程
- **exec()**: 执行新程序
- **kill()**: 发送信号
- **signal()**: 设置信号处理

## 常见问题
- **僵尸进程**: 子进程终止但父进程未wait
- **孤儿进程**: 父进程终止的子进程
- **竞态条件**: 多进程共享资源的问题

## 思考问题

1. 进程和线程的区别?
2. 如何避免僵尸进程?
3. 信号的异步特性带来的挑战?

## 延伸阅读

- [Linux Signal Handling](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Process Management in Linux](https://man7.org/linux/man-pages/man2/fork.2.html)
