#!/bin/bash
source smart-env.sh

dir=$PWD

if [ $1 == "a" ] || [ $1 == "u" ];
then
cd ${dir}/userapps
echo "enter ${dir}/userapps"
scons -j10
python ${dir}/tools/mkromfs.py root ${dir}/kernel/bsp/imx6ull-artpi-smart/applications/romfs.c
../tools/gnu_gcc/arm-linux-musleabi_for_x86_64-pc-linux-gnu/arm-linux-musleabi/bin/objdump -S -d root/bin/lwIPKit.elf > lwip_objdump
fi

if [ $1 == "a" ] || [ $1 == "k" ];
then
cd ${dir}/kernel/bsp/imx6ull-artpi-smart
echo "enter ${dir}/kernel/bsp/imx6ull-artpi-smart"
scons -j10
../../../tools/gnu_gcc/arm-linux-musleabi_for_x86_64-pc-linux-gnu/arm-linux-musleabi/bin/objdump -S -d rtthread.elf > rtthread
fi
    
