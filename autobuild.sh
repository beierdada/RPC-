#!/bin/bash
# 表示这个脚本应该使用Bash解释器来执行,不写的话报错
# #!为特殊标识符，即代表了环境索引。而后面的即是对应环境路径

#有任何错误发生，脚本将停止运行
set -e

rm -rf `pwd`/build/*
cd `pwd`/build &&
	cmake .. &&
	make
cd ..
cp -r `pwd`/src/include `pwd`/lib