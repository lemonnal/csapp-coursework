# Linux 环境搭建指南

## 目录

1. [虚拟机安装](#虚拟机安装)
2. [WSL 安装](#wsl-安装)
3. [开发工具配置](#开发工具配置)
4. [CSAPP 实验环境](#csapp-实验环境)

---

## 虚拟机安装

### 使用 VirtualBox

#### 1. 下载安装 VirtualBox
```bash
# Windows
访问 https://www.virtualbox.org/ 下载安装包

# Ubuntu/Debian
sudo apt-get install virtualbox

# Fedora
sudo dnf install VirtualBox
```

#### 2. 下载 Ubuntu ISO
```bash
# 访问 Ubuntu 官网
https://ubuntu.com/download/desktop

# 推荐版本
Ubuntu 22.04 LTS 或 20.04 LTS
```

#### 3. 创建虚拟机
```bash
# 推荐配置
内存: 4GB+
处理器: 2核+
硬盘: 40GB+
网络: NAT + 桥接
```

#### 4. 安装 Ubuntu
```bash
# 安装过程
1. 选择语言
2. 安装类型: 正常安装
3. 分区: 使用整个磁盘
4. 设置用户名和密码
5. 等待安装完成
```

---

## WSL 安装

### Windows 10/11 安装 WSL

#### 方法 1: 快速安装

```powershell
# PowerShell (管理员)
wsl --install

# 重启计算机
# 安装 Ubuntu
```

#### 方法 2: 手动安装

```powershell
# 启用 WSL 功能
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

# 重启计算机
```

#### 安装 Ubuntu

```powershell
# 打开 Microsoft Store
# 搜索 "Ubuntu"
# 安装 Ubuntu 22.04 LTS
```

#### 配置 WSL

```bash
# 启动 WSL
wsl

# 更新系统
sudo apt update && sudo apt upgrade -y

# 安装基础工具
sudo apt install -y build-essential gdb vim git
```

---

## 开发工具配置

### 必需工具

#### GCC 编译器

```bash
# 安装
sudo apt install -y build-essential

# 验证
gcc --version
make --version
```

#### GDB 调试器

```bash
# 安装
sudo apt install -y gdb

# 配置 .gdbinit
echo "set disassembly-flavor intel" > ~/.gdbinit
echo "set pagination off" >> ~/.gdbinit
```

#### Make 工具

```bash
# 安装
sudo apt install -y make cmake

# 验证
make --version
cmake --version
```

### 辅助工具

#### Valgrind

```bash
# 安装
sudo apt install -y valgrind

# 验证
valgrind --version
```

#### Perf 工具

```bash
# 安装
sudo apt install -y linux-tools-common linux-tools-generic

# 验证
perf --version
```

#### 其他工具

```bash
# 安装
sudo apt install -y \
    git \
    vim \
    emacs \
    tmux \
    htop \
    strace \
    ltrace \
    objdump \
    hexdump
```

---

## CSAPP 实验环境

### 方法 1: 使用 Autolab

```bash
# 注册 CMU Autolab 账号
# 访问 https://autolab.andrew.cmu.edu/

# 下载实验文件
# 按照 Autolab 指导操作
```

### 方法 2: 使用 Docker

```bash
# 安装 Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh

# 拉取 CSAPP Docker 镜像
docker pull csapp/seed-ubuntu:latest

# 运行容器
docker run -it --rm -v $(pwd):/csapp csapp/seed-ubuntu bash

# 在容器内
cd /csapp
# 进行实验操作
```

### 方法 3: 手动配置

#### 安装依赖

```bash
# 更新系统
sudo apt update && sudo apt upgrade -y

# 安装开发工具
sudo apt install -y \
    build-essential \
    gcc \
    gdb \
    make \
    perl \
    tcl \
    tk
```

#### 配置实验环境

```bash
# 创建工作目录
mkdir -p ~/csapp/labs
cd ~/csapp/labs

# 下载实验文件
# (从 CMU 官网下载)
```

---

## 编辑器配置

### VS Code (推荐)

#### 安装

```bash
# 下载 .deb 包
wget https://go.microsoft.com/fwlink/?LinkID=760868

# 安装
sudo apt install ./code_<version>.deb

# 或使用 snap
sudo snap install code --classic
```

#### 推荐插件

```
C/C++
Python
Remote - WSL
GitLens
Bracket Pair Colorizer
Material Icon Theme
One Dark Pro
```

### Vim 配置

#### 创建 .vimrc

```bash
# 创建配置文件
vim ~/.vimrc
```

```vim
" 基本设置
set number              " 显示行号
set tabstop=4           " Tab 宽度
set shiftwidth=4        " 缩进宽度
set expandtab           " 使用空格替代 Tab
set autoindent          " 自动缩进
set smartindent         " 智能缩进
set hlsearch            " 高亮搜索
set incsearch           " 增量搜索
set ignorecase          " 忽略大小写
set smartcase           " 智能大小写
set mouse=a             " 启用鼠标
set encoding=utf-8      " 编码

" 语法高亮
syntax enable
filetype plugin indent on

" 主题
colorscheme desert

" 映射
let mapleader = ","
nnoremap <leader>w :w<CR>
nnoremap <leader>q :q<CR>
nnoremap <leader><space> :nohlsearch<CR>
```

### Emacs 配置

```elisp
;; ~/.emacs
(setq inhibit-startup-screen t)
(menu-bar-mode -1)
(tool-bar-mode -1)
(scroll-bar-mode -1)

;; 显示行号
(global-linum-mode t)

;; Tab 设置
(setq-default tab-width 4)
(setq-default indent-tabs-mode nil)

;; 主题
(load-theme 'tango-dark)
```

---

## Shell 配置

### Bash 配置

```bash
# 编辑 ~/.bashrc
vim ~/.bashrc
```

```bash
# 别名
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'

# 环境变量
export EDITOR=vim
export VISUAL=vim

# PATH
export PATH=$PATH:$HOME/bin

# 历史记录
export HISTSIZE=10000
export HISTCONTROL=ignoredups

# 提示符
PS1='[\u@\h \W]\$ '
```

```bash
# 使配置生效
source ~/.bashrc
```

---

## Git 配置

```bash
# 安装 Git
sudo apt install -y git

# 配置用户信息
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# 配置默认分支
git config --global init.defaultBranch main

# 配置编辑器
git config --global core.editor vim

# 配置别名
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit

# 查看配置
git config --list
```

---

## 测试环境

### 编译测试

```bash
# 创建测试文件
cat > hello.c << EOF
#include <stdio.h>

int main() {
    printf("Hello, CSAPP!\n");
    return 0;
}
EOF

# 编译
gcc -o hello hello.c

# 运行
./hello

# 应该输出: Hello, CSAPP!
```

### 调试测试

```bash
# 使用 GDB
gdb ./hello

# 在 GDB 中
(gdb) break main
(gdb) run
(gdb) next
(gdb) print "Hello"
(gdb) continue
(gdb) quit
```

---

## 常见问题

### 1. 权限问题

```bash
# 将用户添加到 sudo 组
sudo usermod -aG sudo $USER

# 重新登录
```

### 2. 网络问题

```bash
# 检查网络
ping google.com

# 配置 DNS
sudo vim /etc/resolv.conf

# 添加
nameserver 8.8.8.8
nameserver 8.8.4.4
```

### 3. 中文支持

```bash
# 安装中文语言包
sudo apt install -y language-pack-zh-hans

# 设置字符编码
export LANG=zh_CN.UTF-8
export LC_ALL=zh_CN.UTF-8
```

### 4. 性能优化

```bash
# 增加交换空间
sudo fallocate -l 4G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

# 永久生效
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
```

---

## 参考资料

- [Ubuntu 官方文档](https://ubuntu.com/server/docs)
- [WSL 官方文档](https://docs.microsoft.com/en-us/windows/wsl/)
- [VirtualBox 用户手册](https://www.virtualbox.org/manual/UserManual.html)
- [Docker 官方文档](https://docs.docker.com/)
