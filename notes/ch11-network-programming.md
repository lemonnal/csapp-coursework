# 第11章 网络编程

## 核心概念

### 网络基础
- **客户端-服务器模型**: 服务请求者和服务提供者
- **协议**: 通信规则的约定
- **TCP/IP**: 互联网基础协议
- **端口**: 标识不同服务的16位数字

### Socket
- **Socket**: 网络通信的端点
- **IP地址**: 标识主机
- **端口号**: 标识应用
- **连接**: IP地址和端口的组合

### HTTP协议
- **请求方法**: GET, POST, HEAD等
- **状态码**: 200, 404, 500等
- **请求头**: 描述请求的元信息
- **响应头**: 描述响应的元信息

## 难点解析

### TCP vs UDP
- **TCP**: 面向连接,可靠,有序
- **UDP**: 无连接,不可靠,无序
- **选择**: 根据应用需求选择

### Socket编程流程
- **服务器**: socket() -> bind() -> listen() -> accept() -> read()/write()
- **客户端**: socket() -> connect() -> read()/write()
- **关闭**: close()

### IP地址转换
- **inet_pton()**: 字符串转网络字节序
- **inet_ntop()**: 网络字节序转字符串
- **字节序**: 主机序和网络序的转换

### 并发服务器
- **多进程**: 每个连接一个进程
- **多线程**: 每个连接一个线程
- **I/O多路复用**: select/poll/epoll

## 实践联系

### Proxy Lab 关联
- Socket编程
- HTTP协议解析
- 并发处理
- 缓存管理

### TCP服务器示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // 创建socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        return 1;
    }

    // 设置地址复用
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定地址和端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        close(server_fd);
        return 1;
    }

    // 监听连接
    if (listen(server_fd, 5) == -1) {
        perror("listen failed");
        close(server_fd);
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    // 接受连接
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd == -1) {
        perror("accept failed");
        close(server_fd);
        return 1;
    }

    // 接收数据
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        printf("Received: %s\n", buffer);

        // 发送响应
        const char *response = "Hello from server!";
        write(client_fd, response, strlen(response));
    }

    // 关闭连接
    close(client_fd);
    close(server_fd);

    return 0;
}
```

### TCP客户端示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024] = "Hello from client!";

    // 创建socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket failed");
        return 1;
    }

    // 连接服务器
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect failed");
        close(client_fd);
        return 1;
    }

    // 发送数据
    write(client_fd, buffer, strlen(buffer));

    // 接收响应
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
    }

    // 关闭连接
    close(client_fd);

    return 0;
}
```

### 简单HTTP GET请求
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    struct hostent *host;
    char request[1024];
    char response[4096];

    // 创建socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket failed");
        return 1;
    }

    // 获取主机信息
    host = gethostbyname("www.example.com");
    if (host == NULL) {
        perror("gethostbyname failed");
        close(client_fd);
        return 1;
    }

    // 连接服务器
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr.s_addr, host->h_addr, host->h_length);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect failed");
        close(client_fd);
        return 1;
    }

    // 发送HTTP GET请求
    sprintf(request, "GET / HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n");
    write(client_fd, request, strlen(request));

    // 接收响应
    ssize_t bytes_read;
    while ((bytes_read = read(client_fd, response, sizeof(response))) > 0) {
        write(STDOUT_FILENO, response, bytes_read);
    }

    // 关闭连接
    close(client_fd);

    return 0;
}
```

## 性能优化
- **连接池**: 重用连接
- **非阻塞I/O**: 使用select/poll/epoll
- **多线程/多进程**: 并发处理
- **零拷贝**: 减少数据复制

## 调试工具
```bash
# 抓包分析
tcpdump -i eth0 -w capture.pcap port 8080

# 查看网络状态
netstat -an | grep 8080
ss -tulpn | grep 8080

# 测试连接
telnet localhost 8080
curl http://localhost:8080
```

## 思考问题

1. TCP如何保证可靠性?
2. 如何处理网络异常?
3. HTTP 1.1/2.0/3.0的区别?

## 延伸阅读

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [TCP/IP Illustrated](https://www.pearson.com/en-us/subject-catalog/p/tcp-ip-illustrated-volume-1-the-protocols/P200000003537/9780201633467)
- [HTTP/1.1 RFC](https://www.rfc-editor.org/rfc/rfc2616)
