# 第9章 虚拟内存

## 核心概念

### 虚拟内存定义
- **虚拟内存**: 抽象的、逻辑的内存空间
- **物理内存**: 实际的硬件内存
- **虚拟地址**: 虚拟内存中的地址
- **物理地址**: 物理内存中的地址

### 地址翻译
- **页表**: 虚拟页到物理页的映射
- **页表项(PTE)**: 包含物理页号和标志位
- **TLB**: 翻译后备缓冲器,加速地址翻译

### 页面置换
- **缺页异常**: 访问未加载的虚拟页
- **页面置换算法**: 决定替换哪个页面
- **工作集**: 进程活跃使用的页面集合

## 难点解析

### 分页机制
- **页面大小**: 通常4KB
- **页号**: 虚拟地址的高位
- **页偏移**: 虚拟地址的低位
- **多级页表**: 减少页表大小

### TLB (Translation Lookaside Buffer)
- **TLB命中**: 快速地址翻译
- **TLB未命中**: 访问页表
- **TLB刷新**: 更新TLB内容

### 页面置换算法
- **LRU**: 最近最少使用
- **FIFO**: 先进先出
- **随机**: 随机选择
- **Clock**: LRU的近似实现

### 内存映射
- **mmap()**: 将文件映射到内存
- **共享映射**: 多个进程共享同一区域
- **私有映射**: 进程独享的映射

## 实践联系

### Malloc Lab 关联
- 动态内存分配
- 内存对齐
- 碎片处理

### 地址翻译示例
```c
// 虚拟地址: 0x00401234
// 页面大小: 4KB (12位偏移)
// 虚拟页号: 0x00401
// 页偏移: 0x234
// 通过页表查找物理页号
// 物理地址 = (物理页号 << 12) | 页偏移
```

### 内存映射示例
```c
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDWR);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    // 映射文件到内存
    char *mapped = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                        MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // 读取内容
    printf("Content: %s\n", mapped);

    // 解除映射
    munmap(mapped, 4096);
    close(fd);

    return 0;
}
```

### 内存分配示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // 使用mmap分配内存
    void *ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    strcpy((char *)ptr, "Hello, mmap!");
    printf("%s\n", (char *)ptr);

    // 释放内存
    munmap(ptr, 4096);

    return 0;
}
```

## 性能优化
- **大页面**: 减少TLB未命中
- **页面预取**: 提前加载页面
- **页面着色**: 缓存优化
- **NUMA感知**: 多处理器优化

## 调试工具
```bash
# 查看进程内存映射
cat /proc/<pid>/maps
pmap <pid>

# 监控页面错误
perf stat -e page-faults ./program

# 使用valgrind检测内存问题
valgrind --tool=memcheck ./program
```

## 思考问题

1. 虚拟内存的优势是什么?
2. 如何优化TLB的性能?
3. 缺页异常是如何处理的?

## 延伸阅读

- [Understanding the Linux Virtual Memory Manager](https://www.kernel.org/doc/gorman/html/understand/)
- [What Every Programmer Should Know About Memory](https://www.akkadia.org/drepper/cpumemory.pdf)
