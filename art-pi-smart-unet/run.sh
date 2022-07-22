source smart-env.sh

cd userapps
scons -j10
python ../tools/mkromfs.py root ../kernel/bsp/imx6ull-artpi-smart/applications/romfs.c

cd ../kernel/bsp/imx6ull-artpi-smart
scons -j10
    
