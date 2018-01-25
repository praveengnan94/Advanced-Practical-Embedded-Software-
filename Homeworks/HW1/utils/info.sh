#FILE NAME: info.sh, DESCRIPTION: Script to provide system information to the user
#AUTHOR: PRAVEEN GNANASEKARAN
#TOOLS USED: BASH script.
#!/bin/bash -x
echo "User Information"
uname --all 
echo "Operating System Type/Brand"
uname -o 
echo "OS Distribution"
lsb_release -a
echo "OS Version"
cat /etc/*release
echo "Kernel Version"
uname --version
echo "Kernel gcc version build"
cat /proc/version
echo "Kernel Build Time"
uname -v
echo "System Architecture Information"
lscpu 
echo "Information on File System Memory"
df -h
