#FILE NAME: build_kernel.sh, DESCRIPTION: Script to build the 4.14.0 Version of Linux automatically
#AUTHOR: PRAVEEN GNANASEKARAN
#TOOLS USED: BASH script.
#!/bin/bash -x
cd /home/praveen/Desktop/APES/kernel/linux
make -j2
make modules_install -j2
make install -j2