#!/bin/bash
# 定义所有作业的标签
assignments=(
    "c4prj1_deck"
    "c4prj2_input"
    "c4prj3_finish"
)

# 遍历数组，对每个作业调用 fast-forward 命令
for assignment in "${assignments[@]}"; do
  echo "Updating assignment: $assignment"
  fast-forward "$assignment"
done
