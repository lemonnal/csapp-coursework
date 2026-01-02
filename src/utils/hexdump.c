// 简单的十六进制转储工具
// 用于查看文件的二进制内容

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 打印十六进制转储
void hexdump(FILE *fp, const char *filename) {
    unsigned char buffer[16];
    size_t bytes_read;
    size_t offset = 0;
    int i;

    printf("Hex dump of: %s\n", filename);
    printf("=" * 70\n");

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        // 打印偏移量
        printf("%08zx: ", offset);

        // 打印十六进制
        for (i = 0; i < 16; i++) {
            if (i < bytes_read) {
                printf("%02x ", buffer[i]);
            } else {
                printf("   ");
            }

            if (i == 7) {
                printf(" ");
            }
        }

        // 打印ASCII
        printf(" |");
        for (i = 0; i < bytes_read; i++) {
            printf("%c", isprint(buffer[i]) ? buffer[i] : '.');
        }
        printf("|\n");

        offset += bytes_read;
    }

    printf("=" * 70\n");
    printf("Total bytes: %zu\n", offset);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法: %s <文件名>\n", argv[0]);
        fprintf(stderr, "示例: %s test.txt\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("无法打开文件");
        return 1;
    }

    hexdump(fp, argv[1]);

    fclose(fp);
    return 0;
}

// 编译:
// gcc hexdump.c -o hexdump
//
// 使用:
// ./hexdump 文件名
// ./hexdump /bin/ls | head -20
