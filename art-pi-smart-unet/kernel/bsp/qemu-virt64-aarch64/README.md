# QEMU/virt aarch64板级支持包说明

## 1. 简介

The virt board is a platform which does not correspond to any real hardware; it is designed for use in virtual machines.

Supported guest CPU types:
cortex-a7 (32-bit)
cortex-a15 (32-bit; the default)
cortex-a53 (64-bit)
cortex-a57 (64-bit)
cortex-a72 (64-bit)
host (with KVM only)
max (same as host for KVM; best possible emulation with TCG)

Guest code can rely on and hard-code the following addresses:
Flash memory starts at address 0x0000_0000
RAM starts at 0x4000_0000

## 2. 编译说明

推荐使用[env工具][2]，可以在console下进入到`bsp/qemu-virt64-aarch64`目录中，运行以下命令：

    scons

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。

**注：** RT-Thread/ENV中携带的工具版本是：

    gcc version 5.4.1 20160919 (release) [ARM/embedded-5-branch revision 240496]

如果在Linux下使用，请自行下载[GNU GCC工具链][3]。

## 3. 执行

当要执行编译好的RT-Thread时，在这个bsp目录下已经提供了运行脚本文件：qemu.bat/qemu.sh

这个执行脚本默认把串口输出到stdio（即控制台）上，所以直接执行脚本后就可以输出结果了。

```text
 \ | /
- RT -     Thread Smart Operating System
 / | \     5.0.0 build Aug 18 2021
 2006 - 2020 Copyright by rt-thread team
hello rt-thread
msh />
```

## 4. 支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0 |
| SD/MMC | 不支持 |  |
| CLCD | 不支持 |  |
| Key | 不支持 |  |
| Mouse | 不支持 |  |
| EMAC | 不支持 |  |

