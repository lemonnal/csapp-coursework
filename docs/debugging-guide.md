# 调试指南

## 目录

1. [GDB 调试](#gdb-调试)
2. [内存调试](#内存调试)
3. [性能分析](#性能分析)
4. [常见问题](#常见问题)

---

## GDB 调试

### 启动 GDB

```bash
# 调试可执行文件
gdb ./program

# 带参数运行
gdb --args ./program arg1 arg2

# 调试核心转储
gdb ./program core

# 附加到运行中的进程
gdb -p <pid>
```

### 基本调试流程

```bash
# 设置断点
(gdb) break main
(gdb) break 42          # 在当前文件第42行
(gdb) break file.c:50   # 在特定文件特定行
(gdb) break function    # 在函数入口

# 运行程序
(gdb) run
(gdb) run arg1 arg2

# 单步执行
(gdb) next              # 下一行(不进入函数)
(gdb) step              # 下一行(进入函数)
(gdb) nexti             # 下一条机器指令
(gdb) continue          # 继续执行

# 查看信息
(gdb) backtrace         # 查看调用栈
(gdb) frame 0           # 切换到栈帧0
(gdb) up                # 上一个栈帧
(gdb) down              # 下一个栈帧

# 查看变量和内存
(gdb) print var         # 打印变量
(gdb) print *ptr@10     # 打印数组
(gdb) x/10x $rsp        # 查看内存(16进制,10个单位)
(gdb) x/5i $pc          # 查看机器码
(gdb) info registers    # 查看寄存器
(gdb) info locals       # 查看局部变量

# 修改变量
(gdb) set var = 10

# 条件断点
(gdb) break 42 if i == 10

# 监视点
(gdb) watch var         # 当变量改变时停止
(gdb) rwatch var        # 当变量被读时停止
(gdb) awatch var        # 当变量被读写时停止
```

### 汇编级调试

```bash
# 显示汇编代码
(gdb) disassemble main
(gdb) disassemble

# 单步执行指令
(gdb) stepi
(gdb) nexti

# 查看寄存器
(gdb) info registers
(gdb) print $rax
(gdb) print/x $rsp      # 16进制显示

# 查看栈
(gdb) x/20x $rsp        # 查看栈内容
(gdb) x/20gx $rsp       # 查看栈内容(8字节单位)
```

### GDB 脚本

```bash
# 自动运行命令
(gdb) break main
(gdb) commands
> silent
> print argc
> print argv[0]
> continue
> end

# 保存断点
(gdb) save breakpoints my_gdb.bps

# 加载断点
(gdb) source my_gdb.bps
```

### GDB 宏

```bash
# 定义宏
(gdb) define print_array
> set $arr = $arg0
> set $len = $arg1
> set $i = 0
> while $i < $len
>   print $arr[$i]
>   set $i = $i + 1
> end
> end

# 使用宏
(gdb) print_array arr, 10
```

### TUI 模式

```bash
# 启用 TUI
(gdb) layout asm
(gdb) layout src
(gdb) layout split
(gdb) layout regs

# 窗口切换
Ctrl+X, then 1          # 单窗口模式
Ctrl+X, then 2          # 双窗口模式
```

---

## 内存调试

### Valgrind

```bash
# 基本内存检查
valgrind ./program

# 详细报告
valgrind -v ./program

# 内存泄漏检测
valgrind --leak-check=full --show-leak-kinds=all ./program

# 生成可读报告
valgrind --leak-check=full --log-file=valgrind-report.txt ./program

# 检查非法内存访问
valgrind --track-origins=yes ./program

# 缓存分析
valgrind --tool=cachegrind ./program
cg_annotate cachegrind.out.<pid>

# 线程错误检测
valgrind --tool=helgrind ./program
```

### Valgrind 输出解读

```
==12345== Invalid write of size 4
==12345==    at 0x400500: main (test.c:10)
==12345==  Address 0x51f0068 is 0 bytes after a block of size 40 alloc'd
==12345==    at 0x4C2DB8F: malloc (vg_replace_malloc.c:299)

==12345== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x4C2DB8F: malloc (vg_replace_malloc.c:299)
==12345==    by 0x40052E: main (test.c:15)
```

---

## 性能分析

### perf 工具

```bash
# 基本性能统计
perf stat ./program

# CPU 周期和指令
perf stat -e cycles,instructions ./program

# 缓存性能
perf stat -e cache-references,cache-misses,L1-dcache-load-misses ./program

# 分支预测
perf stat -e branches,branch-misses ./program

# 详细分析
perf record ./program
perf report

# 实时分析
perf top

# 火焰图生成
perf record -F 99 -g ./program
perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg
```

### gprof 工具

```bash
# 编译时添加支持
gcc -pg program.c -o program

# 运行程序
./program

# 生成报告
gprof program gmon.out > analysis.txt

# 可视化
gprof2dot -s gmon.out | dot -Tpng -o profile.png
```

### time 命令

```bash
# 实际运行时间
time ./program

# 详细统计
/usr/bin/time -v ./program
```

---

## 常见问题

### 段错误 (Segmentation Fault)

#### 原因
- 空指针解引用
- 数组越界
- 使用已释放的内存
- 栈溢出

#### 调试方法

```bash
# 使用 GDB
gdb ./program
(gdb) run
# 程序崩溃后
(gdb) backtrace    # 查看崩溃位置
(gdb) frame 0      # 切换到崩溃帧
(gdb) print var    # 查看变量值

# 使用 core dump
ulimit -c unlimited
./program
gdb ./program core

# 使用 Valgrind
valgrind ./program
```

### 内存泄漏

#### 检测

```bash
valgrind --leak-check=full --show-leak-kinds=all \
         --leak-resolution=high --show-reachable=yes \
         ./program
```

#### 常见原因
- malloc 没有对应的 free
- 重复分配但只释放一次
- 循环引用
- 异常路径未释放

### 竞态条件

#### 检测

```bash
valgrind --tool=helgrind ./program
valgrind --tool=drd ./program
```

#### 解决方法
- 使用互斥锁保护共享数据
- 避免全局变量
- 使用原子操作

### 死锁

#### 检测方法
- GDB 暂停所有线程,查看锁状态
- 添加调试输出
- 使用死锁检测工具

#### 避免方法
- 统一锁的获取顺序
- 使用超时机制
- 避免嵌套锁

---

## 调试技巧

### printf 调试

```c
// 添加调试输出
fprintf(stderr, "DEBUG: line %d, x = %d\n", __LINE__, x);

// 条件编译
#ifdef DEBUG
    fprintf(stderr, "DEBUG: x = %d\n", x);
#endif

// 宏定义
#define DEBUG_PRINT(fmt, args...) \
    fprintf(stderr, "DEBUG %s:%d: " fmt, __FILE__, __LINE__, ##args)
```

### 断言

```c
#include <assert.h>

// 运行时检查
assert(ptr != NULL);
assert(i >= 0 && i < size);

// 自定义断言
#define ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "Assertion failed: %s\n", msg); \
            exit(1); \
        } \
    } while(0)
```

### 静态分析

```bash
# GCC 静态分析
gcc -Wall -Wextra -fanalyzer program.c

# Clang 静态分析
clang --analyze program.c

# CPPcheck
cppcheck --enable=all program.c

# Splint
splint program.c
```

---

## 实用脚本

### 内存检查脚本

```bash
#!/bin/bash
# memory_check.sh

echo "Running memory check..."
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./program

echo "Memory check complete. See valgrind-out.txt for details."
```

### 性能分析脚本

```bash
#!/bin/bash
# profile.sh

echo "Running performance analysis..."
perf stat -e cycles,instructions,cache-references,cache-misses,branches,branch-misses \
         -o perf-stats.txt \
         ./program

echo "Recording detailed data..."
perf record -g ./program
perf report > perf-report.txt

echo "Analysis complete. See perf-stats.txt and perf-report.txt."
```

---

## 最佳实践

1. **编译时包含调试信息**
   ```bash
   gcc -g -O0 program.c -o program
   ```

2. **使用版本控制**
   - Git 标记已知问题的版本

3. **单元测试**
   - 测试边界条件
   - 测试错误路径

4. **代码审查**
   - 容易发现潜在问题

5. **文档化**
   - 记录已知问题
   - 记录解决方案

---

## 参考资料

- [GDB 官方文档](https://www.gnu.org/software/gdb/documentation/)
- [Valgrind 手册](https://valgrind.org/docs/manual/manual.html)
- [perf 工具指南](https://perf.wiki.kernel.org/)
