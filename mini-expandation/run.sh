#!/bin/bash

# 检查是否提供了文件名参数
if [ $# -eq 0 ]; then
    echo "Usage: $0 <filename>"
    echo "Example: $0 while-bc"
    exit 1
fi

# 获取文件名（去掉可能的 .m 扩展名）
filename=$1
filename=${filename%.m}

# 设置文件路径
m_file="${filename}.m"
s_file="${filename}.s"
o_file="${filename}.o"

# 检查 .m 文件是否存在
if [ ! -f "$m_file" ]; then
    echo "Error: File $m_file not found!"
    exit 1
fi

echo "=========================================="
echo "Compiling and running: $filename"
echo "=========================================="
echo ""

# 步骤1: 运行 mini 编译器生成 .s 文件
echo "Step 1: Running ./mini $m_file"
if ./mini "$m_file"; then
    echo "✓ mini completed successfully"
else
    echo "✗ mini failed"
    exit 1
fi
echo ""

# 检查是否生成了 .s 文件
if [ ! -f "$s_file" ]; then
    echo "Error: $s_file was not generated!"
    exit 1
fi

# 步骤2: 运行 asm 汇编器生成 .o 文件
echo "Step 2: Running ./asm $s_file"
if ./asm "$s_file"; then
    echo "✓ asm completed successfully"
else
    echo "✗ asm failed"
    exit 1
fi
echo ""

# 检查是否生成了 .o 文件
if [ ! -f "$o_file" ]; then
    echo "Error: $o_file was not generated!"
    exit 1
fi

# 步骤3: 运行 machine 虚拟机执行 .o 文件
echo "Step 3: Running ./machine $o_file"
echo "----------------------------------------"
./machine "$o_file"
exit_code=$?
echo "----------------------------------------"
echo ""

if [ $exit_code -eq 0 ]; then
    echo "✓ machine completed successfully"
else
    echo "✗ machine exited with code $exit_code"
    exit $exit_code
fi

echo ""
echo "=========================================="
echo "All steps completed successfully!"
echo "=========================================="

