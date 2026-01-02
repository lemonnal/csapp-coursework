# 第7章 链接

## 核心概念

### 链接的定义
- **链接**: 将各种代码和数据片段收集并组合成单一文件的过程
- **链接器**: 执行链接操作的程序
- **链接时机**: 编译时、加载时、运行时

### 链接类型
- **静态链接**: 在编译时将所有代码合并
- **动态链接**: 在运行时加载共享库

### 可重定位目标文件
- **代码段(.text)**: 机器代码
- **数据段(.data)**: 已初始化全局变量
- **bss段(.bss)**: 未初始化全局变量
- **符号表(.symtab)**: 函数和全局变量信息

## 难点解析

### 符号解析
- **强符号**: 已初始化的全局变量
- **弱符号**: 未初始化的全局变量
- **符号规则**:
  - 不允许多个强符号
  - 强符号和弱符号选择强符号
  - 多个弱符号选择任意一个

### 重定位
- **相对重定位**: 使用相对地址
- **绝对重定位**: 使用绝对地址
- **重定位入口**: 需要重定位的位置

### 静态库
- **归档文件(.a)**: 多个目标文件的集合
- **链接顺序**: 符号依赖的顺序很重要
- **缺点**: 代码重复,更新困难

### 动态库
- **共享对象(.so)**: 运行时加载
- **位置无关代码(PIC)**: 可以加载到任意地址
- **优势**: 节省空间,易于更新

## 实践联系

### 链接命令
```bash
# 静态链接
gcc -static -o program program.c -lc

# 动态链接
gcc -o program program.c

# 指定库路径
gcc -o program program.c -L/path/to/lib -lmylib

# 查看动态库依赖
ldd program

# 查看符号
nm program
readelf -s program
```

### 常见链接错误
```c
// 未定义引用
// error: undefined reference to 'foo'
// 解决: 添加包含foo的库或目标文件

// 多重定义
// error: multiple definition of 'x'
// 解决: 使用static或避免全局变量

// 链接顺序错误
// error: undefined reference to 'bar'
// 解决: 调整库的顺序
```

### 位置无关代码示例
```c
// 使用PIC编译
gcc -fPIC -shared -o libmylib.so mylib.c

// 查看是否为PIC
readelf -d libmylib.so | grep TEXTREL
```

## 链接过程示例
```bash
# 编译多个源文件
gcc -c main.c -o main.o
gcc -c foo.c -o foo.o
gcc -c bar.c -o bar.o

# 链接成可执行文件
gcc -o program main.o foo.o bar.o

# 创建静态库
ar rcs libmylib.a foo.o bar.o

# 使用静态库
gcc -o program main.o -L. -lmylib

# 创建动态库
gcc -fPIC -shared -o libmylib.so foo.c bar.c

# 使用动态库
gcc -o program main.c -L. -lmylib
```

## 调试工具
```bash
# 查看目标文件信息
objdump -h main.o
readelf -h main.o

# 查看符号表
nm main.o
readelf -s main.o

# 查看重定位信息
readelf -r main.o

# 查看动态段
readelf -d program
```

## 思考问题

1. 静态链接和动态链接的优缺点?
2. 如何解决符号冲突?
3. 为什么链接顺序很重要?

## 延伸阅读

- [Linkers and Loaders](http://linker.iecc.com/)
- [ELF Format Specification](https://refspecs.linuxfoundation.org/elf/elf.pdf)
