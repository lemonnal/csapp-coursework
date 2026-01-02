# 第6章 存储器层次结构

## 核心概念

### 存储技术类型
- **寄存器**: CPU内部,最快,最小
- **SRAM**: 缓存,快速,昂贵
- **DRAM**: 主存,较慢,便宜
- **SSD**: 固态硬盘,慢,大容量
- **HDD**: 机械硬盘,最慢,最便宜

### 层次结构原理
- **顶层**: 寄存器(L0)
- **缓存**: L1, L2, L3
- **主存**: DRAM
- **磁盘**: SSD/HDD

### 局部性原理
- **时间局部性**: 重用最近访问的数据
- **空间局部性**: 访问邻近的数据

## 难点解析

### Cache 性能参数
- **命中率**: 命中次数 / 总访问次数
- **缺失率**: 缺失次数 / 总访问次数
- **命中时间**: 访问缓存的时间
- **缺失惩罚**: 从下层取数据的时间

### Cache 映射
- **直接映射**: 每个块只能映射到一个位置
- **组相联映射**: 每个块可映射到一组位置
- **全相联映射**: 每个块可映射到任意位置

### Cache 替换策略
- **LRU**: 最近最少使用
- **随机**: 随机选择
- **FIFO**: 先进先出

### Cache 写策略
- **写直达**: 立即写入主存
- **写回**: 延迟写入主存
- **写分配**: 缺失时加载块
- **不写分配**: 直接写入主存

## 实践联系

### Cache Lab 关联
- 模拟Cache行为
- 优化矩阵转置
- 最大化Cache命中率

### 优化示例
```c
// 低效的矩阵访问(按列访问)
void sum_col_major(int n, int **a) {
    int sum = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            sum += a[i][j];  // 空间局部性差
        }
    }
}

// 高效的矩阵访问(按行访问)
void sum_row_major(int n, int **a) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += a[i][j];  // 空间局部性好
        }
    }
}
```

### 分块技术
```c
// 矩阵乘法 - 分块优化
#define BLOCK_SIZE 8
void matrix_multiply_block(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i += BLOCK_SIZE) {
        for (int j = 0; j < n; j += BLOCK_SIZE) {
            for (int k = 0; k < n; k += BLOCK_SIZE) {
                // 处理一个块
                for (int ii = i; ii < i + BLOCK_SIZE; ii++) {
                    for (int jj = j; jj < j + BLOCK_SIZE; jj++) {
                        for (int kk = k; kk < k + BLOCK_SIZE; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}
```

## 性能分析工具
```bash
# 使用perf分析缓存性能
perf stat -e cache-references,cache-misses ./program

# 使用valgrind的cachegrind工具
valgrind --tool=cachegrind ./program
cg_annotate cachegrind.out.<pid>
```

## 思考问题

1. 为什么需要多级Cache?
2. 如何衡量Cache的性能?
3. 分块技术为什么能提高性能?

## 延伸阅读

- [Cache Performance Optimizations](https://people.eecs.berkeley.edu/~krste/papers/cache85.pdf)
- [What Every Programmer Should Know About Memory](https://www.akkadia.org/drepper/cpumemory.pdf)
