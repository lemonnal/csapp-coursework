# CSAPP 实验指南

## 目录

1. [Data Lab](#data-lab)
2. [Bomb Lab](#bomb-lab)
3. [Attack Lab](#attack-lab)
4. [Cache Lab](#cache-lab)
5. [Shell Lab](#shell-lab)
6. [Malloc Lab](#malloc-lab)
7. [Proxy Lab](#proxy-lab)

---

## Data Lab

### 实验目标
- 使用位操作实现函数
- 理解整数和浮点数的表示
- 限制操作符数量

### 准备工作
```bash
cd labs/data-lab
make
./btest
```

### 常见问题
1. **如何使用位运算?**
   - 使用 &, |, ^, ~, <<, >>

2. **如何处理有符号数?**
   - 理解补码表示
   - 注意右移的符号扩展

3. **如何限制操作符数量?**
   - 规划好操作步骤
   - 利用表达式特性减少操作

---

## Bomb Lab

### 实验目标
- 逆向工程二进制程序
- 理解汇编代码
- 拆除"炸弹"

### 工具使用
```bash
# 反汇编
objdump -d bomb > bomb.asm

# 调试
gdb ./bomb
(gdb) break phase_1
(gdb) run
(gdb) disassemble
(gdb) info registers
```

### 解决策略
1. **从简单阶段开始**: phase_1, phase_2
2. **分析函数调用**: 理解调用约定
3. **跟踪数据流**: 找到关键变量
4. **理解字符串比较**: sscanf, strcmp等

---

## Attack Lab

### 实验目标
- 理解缓冲区溢出
- 利用栈漏洞
- 执行注入代码

### 核心概念
- **栈帧结构**: 返回地址、保存的寄存器
- **缓冲区溢出**: 覆盖返回地址
- **代码注入**: 在栈上执行代码
- **ROP攻击**: 利用现有代码片段

### 实验步骤
1. **分析目标程序**: 找到漏洞点
2. **构造攻击字符串**: 注入代码 + 返回地址
3. **测试注入**: 使用 gdb 验证
4. **完成关卡**: 逐个通过

---

## Cache Lab

### 实验目标
- 实现缓存模拟器
- 优化矩阵转置

### Part A: 缓存模拟
```c
// 关键函数
void access(address addr);
void update_on_hit(cache *cache);
void update_on_miss(cache *cache);
```

### Part B: 矩阵优化
- **分块**: 提高空间局部性
- **对角线处理**: 避免冲突缺失
- **变量复用**: 减少内存访问

---

## Shell Lab

### 实验目标
- 实现Unix shell
- 进程控制
- 信号处理

### 核心功能
- **命令解析**: 解析用户输入
- **进程创建**: fork/exec
- **信号处理**: SIGINT, SIGTSTP
- **作业控制**: 前台/后台

### 实现提示
```c
// 基本框架
while (1) {
    // 读取命令
    // 解析命令
    // 执行命令
    // 等待或继续
}
```

---

## Malloc Lab

### 实验目标
- 实现动态内存分配器
- 优化吞吐量和利用率

### 核心数据结构
```c
typedef struct block_header {
    size_t size;
    int allocated;
    struct block_header *next;
} block_header;
```

### 优化策略
- **分离空闲链表**: 减少搜索时间
- **头部/脚部**: 快速合并
- **放置策略**: 首次适配/最佳适配

---

## Proxy Lab

### 实验目标
- 实现Web代理服务器
- 并发处理请求
- 缓存管理

### 核心功能
- **HTTP解析**: 解析请求和响应
- **并发处理**: 多线程
- **缓存**: 减少网络延迟

### 实现框架
```c
// 主循环
while (1) {
    connfd = Accept(listenfd, ...);
    pthread_create(&tid, NULL, thread_fn, (void *)connfd);
}
```

---

## 通用调试技巧

### GDB 使用
```bash
(gdb) break main        # 设置断点
(gdb) run               # 运行程序
(gdb) next              # 单步执行
(gdb) print variable    # 打印变量
(gdb) backtrace         # 查看调用栈
(gdb) x/10x $rsp        # 查看内存
```

### 性能分析
```bash
# CPU性能
perf stat ./program

# 缓存性能
perf stat -e cache-references,cache-misses ./program

# 内存泄漏
valgrind --leak-check=full ./program
```

---

## 提交检查清单

- [ ] 通过所有测试用例
- [ ] 代码风格一致
- [ ] 添加必要注释
- [ ] 移除调试代码
- [ ] 检查内存泄漏
- [ ] 验证边界条件

---

## 学习资源

- [CSAPP 官方网站](http://csapp.cs.cmu.edu/)
- [课程讲义](https://www.cs.cmu.edu/~213/)
- [讨论论坛](https://piazza.com/class/)
