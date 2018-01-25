#FILE NAME: build_kernel.sh, DESCRIPTION: Script to build the 4.14.0 Version of Linux automatically
#AUTHOR: PRAVEEN GNANASEKARAN
#TOOLS USED: BASH script.
#!/bin/bash -x

#update dependencies
sudo build-essential ncurses-dev xz-utils libssl-dev bc

#Copy boot config version
cp /boot/config-$(uname --r) .config

#actual make and build process
cd /home/praveen/Desktop/APES/kernel/linux
sudo make -j2
sudo make modules_install -j2
sudo make install -j2