#
# File      : dist.py
# This file is part of RT-Thread RTOS
# COPYRIGHT (C) 2006 - 2020, RT-Thread Development Team
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Change Logs:
# Date           Author       Notes
# 2020-10-24     Bernard      Clean code based on mkdist.py of RT-Thread.

import os
import shutil
import datetime

def do_copy_file(src, dst):
    # check source file
    if not os.path.exists(src):
        return

    path = os.path.dirname(dst)
    # mkdir if path not exist
    if not os.path.exists(path):
        os.makedirs(path)

    shutil.copy2(src, dst)

def do_copy_folder(src_dir, dst_dir, ignore=None):
    import shutil
    # check source directory
    if not os.path.exists(src_dir):
        return

    try:
        if os.path.exists(dst_dir):
            shutil.rmtree(dst_dir)
    except:
        print('Deletes folder: %s failed.' % dst_dir)
        return

    shutil.copytree(src_dir, dst_dir, ignore = ignore)

def zip_dist(dist_dir, dist_name):
    import zipfile

    zip_filename = os.path.join(dist_dir)
    zip = zipfile.ZipFile(zip_filename + '-' + datetime.datetime.now().strftime('%Y%m%d') + '.zip', 'w')
    pre_len = len(os.path.dirname(dist_dir))

    for parent, dirnames, filenames in os.walk(dist_dir):
        for filename in filenames:
            pathfile = os.path.join(parent, filename)
            arcname = pathfile[pre_len:].strip(os.path.sep)
            zip.write(pathfile, arcname)

    zip.close()

def MkDist():
    print('make distribution....')

    patterns = ('*.pyc', '*.map', 'rtthread.bin', '.git', '*.o', '.sconsign.dblite', '*.old', 'build')
    patterns_tools = ('*.pyc', '*.map', 'rtthread.bin', '.git', '.sconsign.dblite', '*.old', 'build', 'ld-musl-arm.so.1')
    bsp_patterns = patterns + tuple(['bsp'])
    cconfig_patterns = patterns + tuple(['cconfig.h'])
    userapps_patterns = patterns + tuple(['cconfig.h', 'gnu-apps'])

    ig_patterns = shutil.ignore_patterns(*patterns)
    ig_patterns_tools = shutil.ignore_patterns(*patterns_tools)
    bsp_patterns = shutil.ignore_patterns(*bsp_patterns)
    cconfig_patterns = shutil.ignore_patterns(*cconfig_patterns)

    dist_dir = os.path.join('.', 'rt-smart')

    # rm dist tree
    shutil.rmtree(dist_dir, ignore_errors=True)
    try:
        os.unlink('rt-smart' + '-' + datetime.datetime.now().strftime('%Y%m%d') + '.zip')
    except:
        # ignore file not exist
        pass

    # copy kernel
    print('=> kernel')
    do_copy_folder('kernel', os.path.join(dist_dir, 'kernel'), ignore=bsp_patterns)

    # copy userapps
    print('=> user apps')
    do_copy_folder('userapps', os.path.join(dist_dir, 'userapps'), ignore=userapps_patterns)

    # copy tools
    print('=> tools script')
    do_copy_folder('tools', os.path.join(dist_dir, 'tools'), ignore=ig_patterns_tools)

    # copy BSP
    print('=> bsp')
    do_copy_folder(os.path.join('.', 'kernel', 'bsp', 'qemu-vexpress-a9'), os.path.join(dist_dir, 'kernel', 'bsp', 'qemu-vexpress-a9'), ignore=ig_patterns)
    do_copy_folder(os.path.join('.', 'kernel', 'bsp', 'raspberry-pi', 'raspi4-32'), os.path.join(dist_dir, 'kernel', 'bsp', 'raspberry-pi', 'raspi4-32'), ignore=ig_patterns)
    do_copy_folder(os.path.join('.', 'kernel', 'bsp', 'imx6ull-artpi-smart'), os.path.join(dist_dir, 'kernel', 'bsp', 'imx6ull-artpi-smart'), ignore=ig_patterns)

    # copy files
    do_copy_file(os.path.join('.', 'docs', 'quickstart', 'README.md'), os.path.join(dist_dir, 'README.md'))
    do_copy_file(os.path.join('.', 'smart-env.bat'), os.path.join(dist_dir, 'smart-env.bat'))
    do_copy_file(os.path.join('.', 'smart-env.sh'), os.path.join(dist_dir, 'smart-env.sh'))

    # make zip package
    zip_dist(dist_dir, 'rt-smart')

    print('done!')

if __name__ == "__main__":
    MkDist()
