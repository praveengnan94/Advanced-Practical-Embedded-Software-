#!/bin/bash -x
cd /home/praveen/Desktop/APES/kernel/linux
make -j2
make modules_install -j2
make install -j2