// 算术运算的汇编表示示例
// 用于理解编译器如何生成汇编代码

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int div(int a, int b) {
    return a / b;
}

int mod(int a, int b) {
    return a % b;
}

// 位运算示例
int bitwise_and(int a, int b) {
    return a & b;
}

int bitwise_or(int a, int b) {
    return a | b;
}

int bitwise_xor(int a, int b) {
    return a ^ b;
}

int bitwise_not(int a) {
    return ~a;
}

int left_shift(int a, int b) {
    return a << b;
}

int right_shift(int a, int b) {
    return a >> b;
}

// 查看生成的汇编代码:
// gcc -S -O0 arith_ops.c -o arith_ops.s
