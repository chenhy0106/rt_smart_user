import os
import shutil
import platform
import sys

"""
build steps:
1. match bsp
2. select userapps arch
3. compile sdk/libc (klibc/ulibc)
4. compile sdk/rt-thread
5. compile userapps
6. strip userapps
7. make romfs for userapps to bsp/applications/romfs.c
8. compile kernel
"""

# add bsp you want to compile, they must in a same arch
"""
bsp list:
    arm:    qemu-vexpress-a9, imx6ull-artpi-smart
aarch64:    qemu-virt64-aarch64, raspberry-pi/raspi4-64
riscv64:    qemu-virt64-riscv, d1-allwinner-nezha
    x86:    x86
"""

# default bsp
# bsp_list = ['qemu-vexpress-a9', 'imx6ull-artpi-smart']
bsp_list = ['imx6ull-artpi-smart']

using_klibc = False # True: if you want to compile libc for kernel 
using_ulibc = False # (using_klibc must be True) if you want to compile libc for userapps 
using_strip = True  # strip userapps
using_romfs = True # compile apps to bsp/applications/romfs.c

# extral config
no_userapps = False # compile without userapps
no_kernel   = False # compile without kernel

if using_ulibc == True: # ulibc need klibc
    using_klibc = True

# config buildbot info here
bot_config = {
    'arm': 
    {
        'bsp': [
            'qemu-vexpress-a9', 'imx6ull-artpi-smart', 'imx6ull-100ask-smart'
        ],
        'cc': 'gcc',
        'prefix': 'arm-linux-musleabi-',
        'linux_path': 'arm-linux-musleabi_for_x86_64-pc-linux-gnu',
        'win_path': 'arm-linux-musleabi_for_i686-w64-mingw32',
        'libgcc_path': '',
    },
    'aarch64': 
    {
        'bsp': [
            'raspberry-pi/raspi4-64', 'qemu-virt64-aarch64'
        ],
        'cc': 'gcc',
        'prefix': 'aarch64-linux-musleabi-',
        'linux_path': 'aarch64-linux-musleabi_for_x86_64-pc-linux-gnu',
        'win_path': 'aarch64-linux-musleabi_for_i686-w64-mingw32',
        'libgcc_path': '',
    },
    'riscv64': 
    {
        'bsp': [
            'qemu-virt64-riscv', 'd1-allwinner-nezha'
        ],
        'cc': 'gcc',
        'prefix': 'riscv64-unknown-linux-musl-',
        'linux_path': 'riscv64-linux-musleabi_for_x86_64-pc-linux-gnu',
        'win_path': 'riscv64-linux-musleabi_for_i686-w64-mingw32',
        'libgcc_path': '',
    },
    'i386': 
    {
        'bsp': [
            'x86'
        ],
        'cc': 'gcc',
        'prefix': 'i386-unknown-linux-musl-',
        'linux_path': 'i386-linux-musleabi_for_x86_64-pc-linux-gnu',
        'win_path': 'i386-linux-musleabi_for_i686-w64-mingw32',
        'libgcc_path': 'lib/gcc/i386-unknown-linux-musl/7.3.0/libgcc.a',    # under tool path
    },
}

print('buildbot: One-click compile RT-Thread Smart .')

arch = ''
tgt_path = os.path.abspath('.')

# read config and set environ
for arch_key in bot_config:
    if arch != '':
        break
    arch_val = bot_config[arch_key]
    for bsp in arch_val['bsp']:
        if bsp in bsp_list:
            arch = arch_key
            os.environ['RTT_CC'] = arch_val['cc']
            os.environ['RTT_CC_PREFIX'] = arch_val['prefix']
            if platform.system() == 'Windows':
                os.environ['RTT_EXEC_PATH'] = os.path.join(tgt_path, 'tools', 'gnu_gcc', arch_val['win_path'], 'bin')
            elif platform.system() == 'Linux':
                os.environ['RTT_EXEC_PATH'] = os.path.join(tgt_path, 'tools', 'gnu_gcc', arch_val['linux_path'], 'bin')
            break

if arch == '':
    for bsp in bsp_list:
        print('buildbot: The bsp %s not support now!' % (bsp))
    sys.exit()
if using_ulibc == True and using_klibc == False:
    print('buildbot: Please use ulibc muse using klibc first !')
    sys.exit()

# check all bsp are the same arch
for bsp in bsp_list:
    if bsp not in bot_config[arch]['bsp']:
        print('buildbot: bsp %s not in arch %s! Please use bsp in the same arch !' % (bsp, arch))
        sys.exit()

print('buildbot:      Arch => %s' % arch)
print('buildbot:        CC => %s' % os.environ['RTT_CC'])
print('buildbot:    PREFIX => %s' % os.environ['RTT_CC_PREFIX'])
print('buildbot: EXEC_PATH => %s' % os.environ['RTT_EXEC_PATH'])
print('buildbot:    Target => %s' % tgt_path)

sdk_path = os.path.join(tgt_path, 'sdk')
usr_path = os.path.join(tgt_path, 'userapps')
cfg_path = os.path.join(usr_path, 'configs')
libgcc_path = os.path.join(os.environ['RTT_EXEC_PATH'], '..', bot_config[arch]['libgcc_path'])
klibc_path = os.path.join(tgt_path, 'kernel', 'components', 'libc', 'compilers', 'musl', 'libc', 'lib')

# select userapps arch config
userapps_arch_list = os.listdir(cfg_path)
userapps_has_config = False
for name in userapps_arch_list:
    idx = name.find("def_config_")
    if idx != -1:
        if name.split('_')[2] == arch: # find config
            userapps_has_config = True
            userapps_def_config = os.path.join(cfg_path, name)
            userapps_config = os.path.join(usr_path, '.config')
            print("buildbot: Use userapps deault config %s ." % name)
            shutil.copy(userapps_def_config, userapps_config)
            break

if userapps_has_config == False:
    print("buildbot: I can't find default userapps config for arch %s !" % arch)
    sys.exit()

# build sdk
# kernel libc
if os.path.exists(os.path.join(tgt_path, 'kernel', 'components', 'libc', 'compilers', 'musl', 'libc')):
    shutil.rmtree(os.path.join(tgt_path, 'kernel', 'components', 'libc', 'compilers', 'musl', 'libc'))
if using_klibc:
    print('buildbot: Build libc ...')
    os.chdir(os.path.join(sdk_path, 'libc'))
    if using_ulibc:
        os.system('scons -c --build-ulibc')
        os.system('scons -j6 --build-ulibc')
        os.system('scons install --build-ulibc')
    else:
        os.system('scons -c')
        os.system('scons -j6')
        os.system('scons install')
    print('buildbot: Build libc done .')

def remove_dir(dir_path, keep_files = []):
    """
    remove dir files, but keep files in dir
    """
    dirs = os.listdir(dir_path)
    for file in dirs:
        fpath = os.path.join(dir_path, file)
        if file in keep_files:
            print("buildbot: remove dir skip file:", file)
            continue # skip keep file
        
        if os.path.isfile(fpath):
            os.remove(fpath)
        elif os.path.isdir(fpath):
            shutil.rmtree(fpath)

# librtthread.a
print('buildbot: Build librtthread ...')
if os.path.exists(os.path.join(usr_path, 'sdk', 'include')):
    shutil.rmtree(os.path.join(usr_path, 'sdk', 'include'))
if os.path.exists(os.path.join(usr_path, 'sdk', 'lib')):
    remove_dir(os.path.join(usr_path, 'sdk', 'lib'), ['SConscript'])
if os.path.exists(os.path.join(usr_path, 'sdk', 'rt-thread')):
    remove_dir(os.path.join(usr_path, 'sdk', 'rt-thread'), ['SConscript'])

os.chdir(os.path.join(sdk_path, 'rt-thread'))
os.system('scons -c')
os.system('scons -j6')
os.system('scons install')
print('buildbot: Build librtthread done .')

# libdbkit.a
# print('buildbot: Build libdbkit ...')
# os.chdir(os.path.join(sdk_path, 'libdbkit'))
# os.system('scons -c')
# os.system('scons -j6')
# os.system('scons install')
# print('buildbot: Build libdbkit done .')

if no_userapps == False:
    # build userapps
    print('buildbot: Build userapps ...')
    os.chdir(usr_path)
    os.system('scons -c')
    os.system('scons -j6')
    print('buildbot: Build userapps done .')

def copy_libgcc(libgcc_path, libc_path):
    shutil.copy(libgcc_path, libc_path)

def build_romfs(target_path, bsp_path, using_romfs=True):
    # build romfs
    if using_romfs:
        os.system('python %s root %s' %(os.path.join(target_path, 'tools', 'mkromfs.py'), os.path.join(bsp_path, 'applications', 'romfs.c')))

def build_sd(bsp_name, size_kb=65536, using_sd=True):
    # build sd.bin
    if using_sd:
        os.system('dd if=/dev/zero of=sd.bin bs=1024 count='+str(size_kb))
        os.system('mkfs.fat sd.bin')
        os.system('mcopy -i sd.bin root/bin/*.elf ::')
        os.system('cp sd.bin ../kernel/bsp/' + bsp_name)

# strip elf files
if using_strip and no_userapps == False:
    print('buildbot: Strip userapps ...')
    os.chdir(usr_path)
    if not os.path.exists(os.path.join('root', 'mnt')):
        os.mkdir(os.path.join('root', 'mnt'))
    os.system('%s root/bin/*.elf' % os.path.join(os.environ['RTT_EXEC_PATH'], bot_config[arch]['prefix'] + 'strip') )
    print('buildbot: Strip userapps done .')

if no_kernel == True:
    sys.exit()

for bsp in bsp_list:
    bsp_path = os.path.join(tgt_path, 'kernel', 'bsp', bsp)
    print('buildbot: Build bsp %s ...' % bsp)
    # Add extension here
    if bsp == 'qemu-vexpress-a9':
        os.chdir(usr_path)
        build_sd(bsp, using_sd=True)
    elif bsp == 'x86':
        if using_klibc:
            copy_libgcc(libgcc_path, klibc_path)
    
    build_romfs(tgt_path, bsp_path, using_romfs)
    # build kernel
    os.chdir(bsp_path)
    os.system('scons -c')
    os.system('scons -j6')
    print('buildbot: Build bsp %s done .' % bsp)
