# 第3章 程序的机器级表示

## 核心概念

### 汇编语言基础
- **指令集架构(ISA)**: x86-64
- **寄存器**: %rax, %rbx, %rcx, %rdx, %rsi, %rdi, %rsp, %rbp等
- **操作数**: 立即数、寄存器、内存引用

### 数据格式
- **字节**: 1字节 (movb)
- **字**: 2字节 (movw)
- **双字**: 4字节 (movl)
- **四字**: 8字节 (movq)

### 控制流
- **条件码**: CF, ZF, SF, OF
- **跳转指令**: jmp, je, jne, jl, jg等
- **条件传送**: cmov

## 难点解析

### 寻址模式
- **直接寻址**: movq $10, %rax
- **间接寻址**: movq (%rax), %rbx
- **变址寻址**: movq 8(%rax), %rcx
- **比例变址**: movq (%rax, %rcx, 4), %rdx

### 栈帧结构
- **栈指针(%rsp)**: 指向栈顶
- **帧指针(%rbp)**: 指向当前栈帧
- **返回地址**: 保存在栈中
- **局部变量**: 在栈帧中分配

### 函数调用约定
- **参数传递**: 前六个参数通过寄存器(%rdi, %rsi, %rdx, %rcx, %r8, %r9)
- **返回值**: 通过%rax寄存器
- **栈对齐**: 栈指针必须16字节对齐

## 实践联系

### Bomb Lab 关联
- 逆向分析二进制程序
- 理解函数调用机制
- 分析控制流和数据流

### 调试技巧
```bash
# 使用 GDB 反汇编
(gdb) disassemble main

# 查看寄存器状态
(gdb) info registers

# 单步执行
(gdb) stepi
```

### 常见汇编模式
- 函数序言: pushq %rbp; movq %rsp, %rbp
- 函数结语: popq %rbp; ret
- 栈分配: subq $N, %rsp
- 栈释放: addq $N, %rsp

## 代码示例

```c
// C 代码
int swap(int *xp, int *yp) {
    int t = *xp;
    *xp = *yp;
    *yp = t;
    return t;
}
```

```asm
# 对应的汇编代码
swap:
    movl (%rdi), %eax      # t = *xp
    movl (%rsi), %edx      # 临时存储 *yp
    movl %edx, (%rdi)      # *xp = *yp
    movl %eax, (%rsi)      # *yp = t
    ret                    # 返回 t
```

## 思考问题

1. 为什么需要调用约定？
2. 栈帧的作用是什么？
3. 如何通过汇编代码理解程序性能？

## 延伸阅读

- [x86-64 Assembly Language Reference](https://www.felixcloutier.com/x86/)
- [Intel 64 and IA-32 Architectures Software Developer's Manual](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
