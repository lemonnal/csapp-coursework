# CSAPP 学习仓库

> 《深入理解计算机系统》（Computer Systems: A Programmer's Perspective）课程学习库  
例程部分由AI生成，本人自己编写的事后会补上）  

## 📚 项目概述

本仓库是我的《深入理解计算机系统》（CS:APP）课程学习记录，包含了课程作业、学习笔记和代码实现

## 环境

Windows for Linux  
Ubuntu 24:04

## 🗂️ 仓库结构

```
├── labs/              # 实验作业
│   ├── data-lab/      # 数据表示实验（位操作）
│   ├── bomb-lab/      # 二进制炸弹实验（汇编与调试）
│   ├── attack-lab/    # 缓冲区溢出攻击实验
│   ├── cache-lab/     # 缓存模拟与优化实验
│   ├── shell-lab/     # 简易Shell实现（进程控制）
│   ├── malloc-lab/    # 动态内存分配器实现
│   └── proxy-lab/     # Web代理服务器实现
│
├── notes/             # 学习笔记
│   ├── ch01-introduction.md
│   ├── ch02-representation.md
│   ├── ch03-machine-language.md
│   ├── ch04-processor-architecture.md
│   ├── ch05-optimization.md
│   ├── ch06-memory-hierarchy.md
│   ├── ch07-linking.md
│   ├── ch08-exceptional-control-flow.md
│   ├── ch09-virtual-memory.md
│   ├── ch10-system-io.md
│   ├── ch11-network-programming.md
│   └── ch12-concurrent-programming.md
│
├── src/               # 示例代码和工具
│   ├── assembly/      # 汇编语言示例
│   ├── memory/        # 内存相关代码
│   ├── concurrency/   # 并发编程示例
│   └── utils/         # 实用工具脚本
│
├── docs/              # 文档和参考资料
├── resources/         # 学习资源链接
└── README.md          # 本文件
```

## 🔬 实验项目详情

### 1. Data Lab (数据表示实验)
- **主题**：位操作和整数/浮点数表示
- **技能**：位运算、二进制补码、IEEE 754浮点标准
- **挑战**：使用有限操作符实现特定功能

### 2. Bomb Lab (二进制炸弹实验)
- **主题**：汇编语言和调试技术
- **技能**：GDB调试、反汇编分析、逆向工程
- **挑战**：通过逆向分析拆除"二进制炸弹"

### 3. Attack Lab (攻击实验)
- **主题**：缓冲区溢出和代码注入
- **技能**：栈结构理解、漏洞利用、安全编程
- **挑战**：利用缓冲区漏洞执行任意代码

### 4. Cache Lab (缓存实验)
- **主题**：缓存层次结构和优化
- **技能**：缓存模拟、矩阵转置优化、空间局部性利用
- **挑战**：最大化缓存命中率

### 5. Shell Lab (Shell实验)
- **主题**：进程控制和信号处理
- **技能**：进程创建、信号处理、作业控制
- **挑战**：实现支持作业控制的Unix Shell

### 6. Malloc Lab (内存分配实验)
- **主题**：动态内存分配
- **技能**：显式空闲链表、分离空闲链表、内存对齐
- **挑战**：实现高效的malloc/free/realloc

### 7. Proxy Lab (代理实验)
- **主题**：网络编程和并发
- **技能**：Socket编程、HTTP协议、并发服务器设计
- **挑战**：实现多线程Web代理服务器


## 🛠️ 环境配置

### 基本要求
- **操作系统**：Linux (推荐Ubuntu) 或 macOS
- **编译器**：GCC (版本 >= 4.8)
- **调试器**：GDB
- **构建工具**：Make

### 快速开始
```bash
# 克隆仓库
git clone https://github.com/lemonnal/csapp-coursework.git

# 进入项目目录
cd csapp-coursework

# 编译所有实验（如果存在Makefile）
make

# 运行特定实验，例如：
cd labs/data-lab
make
./btest
```

### Docker环境（可选）
```bash
# 使用预配置的CSAPP Docker环境
docker run -it --rm -v $(pwd):/csapp csapp/seed-ubuntu bash
```


### 调试技巧
- 使用`gdb`逐步调试复杂程序
- 利用`valgrind`检测内存错误
- 编写测试用例验证边界条件
- 使用`printf`调试与日志记录

### 常见挑战
- **汇编语言**：建议先掌握基础指令和寻址方式
- **内存管理**：理解虚拟内存到物理内存的映射
- **并发编程**：注意竞态条件和同步机制
- **系统调用**：熟悉Unix系统调用接口

## 📈 学习进度

| 章节 | 状态 | 实验完成 | 笔记完成 |
|------|------|----------|----------|
| 第1章 计算机系统漫游 | ⏳ | - | ⏳ |
| 第2章 信息的表示和处理 | ⏳ | Data Lab ⏳ | ⏳ |
| 第3章 程序的机器级表示 | ⏳ | Bomb Lab ⏳ | ⏳ |
| 第4章 处理器体系结构 | ⏳ | - | ⏳ |
| 第5章 优化程序性能 | ⏳ | - | ⏳ |
| 第6章 存储器层次结构 | ⏳ | Cache Lab ⏳ | ⏳ |
| 第7章 链接 | ⏳ | - | ⏳ |
| 第8章 异常控制流 | ⏳ | - | ⏳ |
| 第9章 虚拟内存 | ⏳ | - | ⏳ |
| 第10章 系统级I/O | ⏳ | - | ⏳ |
| 第11章 网络编程 | ⏳ | Proxy Lab ⏳ | ⏳ |
| 第12章 并发编程 | ⏳ | - | ⏳ |

✅ 已完成 🔄 进行中 ⏳ 未开始

## 🤝 贡献与交流

虽然这是我的个人学习记录，但欢迎：

1. **问题反馈**：如果发现错误或不准确的地方
2. **建议改进**：对笔记或代码的改进建议
3. **讨论交流**：通过Issue讨论相关技术问题

## 📚 参考资料

### 核心教材
- [CS:APP 官方网站](http://csapp.cs.cmu.edu/)

### 在线资源
- [CMU 15-213 课程页面](https://www.cs.cmu.edu/afs/cs/academic/class/15213-f23/www/)
- [CS:APP 视频讲座](https://www.bilibili.com/video/BV1iW411d7hd)
- [深入理解计算机系统（中文社区）](https://hansimov.gitbook.io/csapp/)

### 工具资源
- [GDB 调试指南](https://sourceware.org/gdb/current/onlinedocs/gdb/)
- [Valgrind 内存调试工具](http://valgrind.org/)
- [Linux man pages](https://man7.org/linux/man-pages/)

## 📄 许可证

本仓库内容遵循以下原则：
- **实验代码**：仅用于学习和研究目的
- **学习笔记**：CC BY-NC-SA 4.0 许可证
- **个人实现**：MIT 许可证

详情请见 [LICENSE](LICENSE) 文件。


---

**持续更新中** ⚡

*学习的旅程永无止境，每一次深入理解都带来新的惊喜。*