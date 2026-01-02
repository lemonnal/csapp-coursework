# CSAPP 速查表

## 位操作

### 常用操作
```c
// 获取某位
int get_bit(int x, int n) {
    return (x >> n) & 1;
}

// 设置某位为1
int set_bit(int x, int n) {
    return x | (1 << n);
}

// 清除某位
int clear_bit(int x, int n) {
    return x & ~(1 << n);
}

// 切换某位
int toggle_bit(int x, int n) {
    return x ^ (1 << n);
}

// 判断是否为2的幂
int is_power_of_2(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

// 获取最低置位
int get_lowest_set_bit(int x) {
    return x & (-x);
}

// 清除最低置位
int clear_lowest_set_bit(int x) {
    return x & (x - 1);
}
```

---

## 汇编指令

### 数据传送
```asm
movq Src, Dst     # 传送四字
movzbq Src, Dst   # 零扩展字节到四字
movsbq Src, Dst   # 符号扩展字节到四字
pushq Src         # 压栈
popq Dst          # 出栈
```

### 算术运算
```asm
addq Src, Dst     # 加法
subq Src, Dst     # 减法
imulq Src, Dst    # 有符号乘法
cqto              # 符号扩展 %rax 到 %rdx
idivq Divisor     # 有符号除法
```

### 逻辑运算
```asm
andq Src, Dst     # 与
orq Src, Dst      # 或
xorq Src, Dst     # 异或
notq Dst          # 非
salq k, Dst       # 左移
sarq k, Dst       # 算术右移
shrq k, Dst       # 逻辑右移
```

### 控制流
```asm
jmp Label         # 无条件跳转
je Label          # 相等跳转
jne Label         # 不相等跳转
js Label          # 负数跳转
jns Label         # 非负数跳转
call Label        # 调用函数
ret               # 返回
```

### 条件传送
```asm
cmovl Src, Dst    # 小于则传送
cmovle Src, Dst   # 小于等于则传送
cmovg Src, Dst    # 大于则传送
cmovge Src, Dst   # 大于等于则传送
```

---

## 系统调用

### 常用系统调用
```c
// 进程控制
pid_t fork(void);              // 创建子进程
void exit(int status);         // 终止进程
pid_t wait(int *status);       // 等待子进程
pid_t waitpid(pid_t pid, int *status, int options);

// 执行程序
int execve(const char *filename, char *const argv[], char *const envp[]);

// 文件操作
int open(const char *pathname, int flags, mode_t mode);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
int close(int fd);

// 信号
sighandler_t signal(int signum, sighandler_t handler);
int kill(pid_t pid, int sig);
unsigned int alarm(unsigned int seconds);

// 内存映射
void *mmap(void *addr, size_t length, int prot, int flags,
           int fd, off_t offset);
int munmap(void *addr, size_t length);
```

---

## 线程操作

### POSIX 线程
```c
// 线程创建和终止
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
void pthread_exit(void *retval);
int pthread_join(pthread_t thread, void **retval);

// 互斥锁
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

// 条件变量
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_destroy(pthread_cond_t *cond);
```

---

## GDB 命令

### 基本命令
```bash
(gdb) break function     # 设置断点
(gdb) run                # 运行程序
(gdb) next               # 单步执行(不进入函数)
(gdb) step               # 单步执行(进入函数)
(gdb) continue           # 继续执行
(gdb) finish             # 执行到当前函数返回
```

### 信息查看
```bash
(gdb) backtrace          # 查看调用栈
(gdb) frame n            # 切换栈帧
(gdb) info registers     # 查看寄存器
(gdb) info locals        # 查看局部变量
(gdb) print var          # 打印变量
(gdb) x/10x $rsp         # 查看内存(十六进制)
(gdb) x/10i $pc          # 查看指令
```

### 断点管理
```bash
(gdb) break main         # 在main函数设置断点
(gdb) break *0x400500    # 在地址设置断点
(gdb) delete breakpoints # 删除所有断点
(gdb) disable breakpoints# 禁用所有断点
```

---

## 编译选项

### GCC 常用选项
```bash
# 基本编译
gcc -c program.c              # 只编译不链接
gcc -o program program.c      # 指定输出文件名

# 优化
gcc -O0 program.c             # 无优化
gcc -O1 program.c             # 基本优化
gcc -O2 program.c             # 标准优化
gcc -O3 program.c             # 高级优化
gcc -Os program.c             # 优化代码大小

# 调试
gcc -g program.c              # 包含调试信息
gcc -pg program.c             # 生成gprof信息

# 警告
gcc -Wall program.c           # 所有警告
gcc -Werror program.c         # 警告视为错误

# 预处理
gcc -E program.c              # 只进行预处理
gcc -S program.c              # 生成汇编代码

# 线程
gcc -pthread program.c        # 支持POSIX线程

# 库
gcc -L/path/to/lib program.c -lmylib
```

---

## Makefile 模板

```makefile
CC = gcc
CFLAGS = -Wall -Werror -O2 -g
LDFLAGS = -pthread

TARGET = program
OBJS = main.o foo.o bar.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
```

---

## 性能分析

### perf 工具
```bash
# CPU性能分析
perf stat ./program

# 详细分析
perf record ./program
perf report

# 特定事件
perf stat -e cycles,instructions,cache-misses ./program

# 火焰图
perf record -F 99 -a --call-graph dwarf ./program
perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg
```

### valgrind 工具
```bash
# 内存泄漏检测
valgrind --leak-check=full --show-leak-kinds=all ./program

# 缓存分析
valgrind --tool=cachegrind ./program
cg_annotated cachegrind.out.<pid>

# 线程错误检测
valgrind --tool=helgrind ./program
```

---

## 常见错误处理

### 段错误 (Segmentation Fault)
- 使用 gdb 调试
- 检查空指针
- 检查数组越界
- 使用 valgrind 检测内存问题

### 内存泄漏
- 使用 valgrind 检测
- 确保 malloc/free 配对
- 检查所有路径都有释放

### 竞态条件
- 使用互斥锁保护共享数据
- 使用 helgrind 检测
- 避免死锁

---

## 快速参考

| 主题 | 关键点 |
|------|--------|
| 位操作 | 掩码、移位、逻辑运算 |
| 汇编 | 寄存器、指令、栈帧 |
| 链接 | 符号、重定位、库 |
| 进程 | fork、exec、wait |
| 信号 | signal、sigaction |
| 虚拟内存 | 页表、TLB、缺页 |
| 缓存 | 局部性、命中率、分块 |
| 并发 | 互斥锁、条件变量、死锁 |
