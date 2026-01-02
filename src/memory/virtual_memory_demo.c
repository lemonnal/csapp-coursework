// 虚拟内存示例
// 演示虚拟内存的使用

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

void演示_malloc() {
    printf("=== malloc/free 示例 ===\n");

    // 分配内存
    int *arr = (int *)malloc(10 * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        return;
    }

    // 使用内存
    for (int i = 0; i < 10; i++) {
        arr[i] = i * i;
    }

    // 打印结果
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 释放内存
    free(arr);
}

void演示_mmap() {
    printf("\n=== mmap/munmap 示例 ===\n");

    // 使用 mmap 分配内存
    size_t length = 4096;  // 一页
    void *ptr = mmap(NULL, length, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return;
    }

    printf("mmap分配的地址: %p\n", ptr);

    // 写入数据
    strcpy((char *)ptr, "Hello, mmap!");

    // 读取数据
    printf("内容: %s\n", (char *)ptr);

    // 解除映射
    munmap(ptr, length);
}

void演示_memory_map_file() {
    printf("\n=== 文件内存映射示例 ===\n");

    // 创建临时文件
    FILE *fp = fopen("/tmp/mmap_test.txt", "w+");
    if (fp == NULL) {
        perror("fopen failed");
        return;
    }

    // 写入数据
    const char *text = "Hello, File Mapping!";
    fwrite(text, 1, strlen(text), fp);
    fclose(fp);

    // 内存映射
    int fd = open("/tmp/mmap_test.txt", O_RDWR);
    if (fd == -1) {
        perror("open failed");
        return;
    }

    void *mapped = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                        MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return;
    }

    printf("映射文件内容: %s\n", (char *)mapped);

    // 修改内容
    strcat((char *)mapped, " Modified!");

    // 同步到磁盘
    msync(mapped, 4096, MS_SYNC);

    printf("修改后内容: %s\n", (char *)mapped);

    // 清理
    munmap(mapped, 4096);
    close(fd);
    unlink("/tmp/mmap_test.txt");
}

void演示_page_size() {
    printf("\n=== 页面信息 ===\n");

    // 获取页面大小
    long page_size = sysconf(_SC_PAGESIZE);
    printf("页面大小: %ld 字节\n", page_size);

    // 获取物理页面数
    long num_pages = sysconf(_SC_PHYS_PAGES);
    printf("物理页面数: %ld\n", num_pages);

    // 计算总物理内存
    long total_mem = num_pages * page_size;
    printf("总物理内存: %.2f GB\n", (double)total_mem / (1024 * 1024 * 1024));
}

int main() {
    演示_malloc();
    演示_mmap();
    演示_memory_map_file();
    演示_page_size();

    return 0;
}
