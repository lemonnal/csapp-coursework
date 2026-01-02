# 第5章 优化程序性能

## 核心概念

### 优化原则
1. **正确性优先**: 保证程序正确性
2. **度量驱动**: 基于性能度量进行优化
3. **热点优先**: 优化最耗时的部分

### 性能度量
- **CPU周期数**: 执行时间的基本单位
- **CPI**: 每指令周期数
- **性能分析工具**: perf, gprof

### 优化技术
- **代码移动**: 将不变计算移出循环
- **减少过程调用**: 减少函数调用开销
- **循环展开**: 减少循环控制开销
- **提高并行性**: 利用多级操作

## 难点解析

### 现代处理器特性
- **指令级并行**: 多个指令同时执行
- **超标量**: 每周期发射多条指令
- **乱序执行**: 打破指令顺序限制
- **投机执行**: 预测分支执行

### 内存访问优化
- **缓存友好**: 利用空间局部性和时间局部性
- **预取**: 提前加载数据
- **对齐**: 提高内存访问效率

### 分支预测
- **静态预测**: 基于代码模式
- **动态预测**: 基于运行时行为
- **预测失败**: 性能损失

## 实践联系

### 优化示例
```c
// 未优化版本
void sum_array(int *a, int n, int *result) {
    for (int i = 0; i < n; i++) {
        *result += a[i];
    }
}

// 优化版本1: 消除循环依赖
void sum_array_opt1(int *a, int n, int *result) {
    int sum = *result;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    *result = sum;
}

// 优化版本2: 循环展开
void sum_array_opt2(int *a, int n, int *result) {
    int sum = *result;
    int i;
    for (i = 0; i < n - 3; i += 4) {
        sum += a[i];
        sum += a[i + 1];
        sum += a[i + 2];
        sum += a[i + 3];
    }
    for (; i < n; i++) {
        sum += a[i];
    }
    *result = sum;
}
```

### 性能分析工具
```bash
# 使用Linux perf工具
perf stat ./program

# 生成性能报告
perf record ./program
perf report

# 使用gprof分析
gcc -pg program.c -o program
./program
gprof program gmon.out > analysis.txt
```

## 优化检查清单

- [ ] 消除不必要的内存引用
- [ ] 减少函数调用开销
- [ ] 使用循环展开
- [ ] 提高并行性
- [ ] 利用SIMD指令
- [ ] 优化内存访问模式
- [ ] 减少分支预测失败
- [ ] 使用内联函数

## 思考问题

1. 过度优化会带来什么问题？
2. 如何权衡代码可读性和性能？
3. 编译器优化能替代手动优化吗？

## 延伸阅读

- [GCC Optimization Options](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)
- [Performance Optimization Guide](https://easyperf.net/blog/)
