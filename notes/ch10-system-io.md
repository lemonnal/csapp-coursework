# 第10章 系统级I/O

## 核心概念

### I/O 基础
- **文件**: 字节序列
- **文件描述符**: 非负整数,标识打开的文件
- **标准输入/输出/错误**: 0, 1, 2
- **缓冲**: 减少系统调用次数

### I/O 函数分类
- **无缓冲I/O**: 直接系统调用
- **带缓冲I/O**: 标准库函数
- **I/O库函数**: 更高级的抽象

### 文件系统
- **路径**: 绝对路径和相对路径
- **目录**: 文件夹结构
- **链接**: 硬链接和符号链接
- **权限**: 用户/组/其他权限

## 难点解析

### 文件操作
- **打开**: open() 获取文件描述符
- **读取**: read() 从文件读取数据
- **写入**: write() 向文件写入数据
- **定位**: lseek() 设置文件位置
- **关闭**: close() 释放资源

### 标准I/O vs 系统I/O
- **标准I/O**: 带缓冲,高效,易用
- **系统I/O**: 无缓冲,灵活,底层
- **选择**: 根据需求选择合适的接口

### I/O重定向
- **dup2()**: 复制文件描述符
- **管道**: 进程间通信
- **重定向**: 改变输入输出目标

### 文件元数据
- **stat()**: 获取文件状态
- **fstat()**: 获取文件状态(通过fd)
- **lstat()**: 获取符号链接状态

## 实践联系

### 基本文件操作
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    // 打开文件
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    // 写入数据
    const char *msg = "Hello, Unix I/O!\n";
    ssize_t bytes_written = write(fd, msg, 20);
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return 1;
    }

    // 定位到文件开头
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek failed");
        close(fd);
        return 1;
    }

    // 读取数据
    char buf[100];
    ssize_t bytes_read = read(fd, buf, sizeof(buf));
    if (bytes_read == -1) {
        perror("read failed");
        close(fd);
        return 1;
    }

    // 输出读取的内容
    write(STDOUT_FILENO, buf, bytes_read);

    // 关闭文件
    close(fd);

    return 0;
}
```

### 获取文件元数据
```c
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

void print_file_info(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == -1) {
        perror("stat failed");
        return;
    }

    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", st.st_size);
    printf("Permissions: %o\n", st.st_mode & 0777);
    printf("Last modified: %s", ctime(&st.st_mtime));

    if (S_ISREG(st.st_mode)) {
        printf("Type: Regular file\n");
    } else if (S_ISDIR(st.st_mode)) {
        printf("Type: Directory\n");
    }
}

int main() {
    print_file_info("test.txt");
    return 0;
}
```

### I/O重定向示例
```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    // 重定向stdout到文件
    dup2(fd, STDOUT_FILENO);
    close(fd);

    printf("This will be written to output.txt\n");
    printf("Not to the terminal\n");

    return 0;
}
```

### 标准I/O vs 系统I/O对比
```c
// 系统I/O (无缓冲)
int fd = open("test.txt", O_RDONLY);
char buf[1024];
read(fd, buf, sizeof(buf));
close(fd);

// 标准I/O (带缓冲)
FILE *fp = fopen("test.txt", "r");
char buf[1024];
fread(buf, 1, sizeof(buf), fp);
fclose(fp);
```

## 性能考虑
- **缓冲区大小**: 选择合适的缓冲区大小
- **批量操作**: 减少系统调用次数
- **内存映射**: 大文件操作使用mmap
- **异步I/O**: 不阻塞的I/O操作

## 常见错误
- **忘记检查返回值**: 系统调用可能失败
- **资源泄漏**: 忘记关闭文件描述符
- **竞态条件**: 多进程/线程访问文件
- **原子操作**: 使用O_APPEND保证原子性

## 调试工具
```bash
# 查看打开的文件描述符
ls -la /proc/<pid>/fd

# 使用strace跟踪系统调用
strace -e trace=open,read,write ./program

# 使用ltrace跟踪库函数
ltrace ./program
```

## 思考问题

1. 为什么需要标准I/O库?
2. 如何实现原子性的文件操作?
3. I/O性能瓶颈在哪里?

## 延伸阅读

- [Linux File API Documentation](https://man7.org/linux/man-pages/man2/open.2.html)
- [Advanced Programming in the UNIX Environment](https://www.pearson.com/en-us/subject-catalog/p/advanced-programming-in-the-unix-environment/P200000003498/9780134906129)
