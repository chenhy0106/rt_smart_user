import os

smart_root = os.path.dirname(os.path.abspath(__file__))
citest_dir = os.path.join(smart_root, 'tools', 'ci-test')
kernel_dir = os.path.join(smart_root, 'kernel')
gnuapp_dir = os.path.join(smart_root, 'userapps', 'gnu-apps')
libc_dir   = os.path.join(smart_root, 'sdk', 'libc')

def clone_update(path, url, branch = 'master'):
    if os.path.exists(path):
        os.chdir(path)
        os.system('git pull origin %s' % branch)
    else:
        os.chdir(os.path.dirname(path))
        os.system('git clone %s %s' %(url, os.path.basename(path)))

def branch_update(path, branch = 'master'):
    os.chdir(path)
    os.system('git pull origin %s' % branch)

# clone_update(citest_dir, 'https://git.rt-thread.com/alliance/rt-smart/ci-build.git')
clone_update(gnuapp_dir, 'https://git.rt-thread.com/alliance/rt-smart/gnu-apps.git')

# update submodule
os.chdir(smart_root)
os.system('git submodule init')

branch_update(kernel_dir, 'rt-smart')

# not update libc
# branch_update(libc_dir)
