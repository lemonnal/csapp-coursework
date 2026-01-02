# 汇编语言示例 - Hello World
# 使用 x86-64 汇编编写

.section .data
    msg: .ascii "Hello, Assembly!\n"  # 要输出的消息
    len = . - msg                       # 消息长度

.section .text
    .global _start

_start:
    # sys_write 系统调用
    # 参数: fd=1(STDOUT), buf=msg, count=len
    movq $1, %rax        # 系统调用号: 1 (sys_write)
    movq $1, %rdi        # 文件描述符: 1 (STDOUT)
    movq $msg, %rsi      # 消息地址
    movq $len, %rdx      # 消息长度
    syscall              # 执行系统调用

    # sys_exit 系统调用
    # 参数: error_code=0
    movq $60, %rax       # 系统调用号: 60 (sys_exit)
    movq $0, %rdi        # 退出码: 0
    syscall              # 执行系统调用
