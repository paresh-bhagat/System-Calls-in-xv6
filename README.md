
# System Calls in xv6

## xv6

Xv6 is a re-implementation of the Unix sixth edition in order to use as a learning tool.xv6 is that it contains all the core Unix concepts and has a similar structure to Unix even though it lacks some functionality that you would expect from a modern operating system. This is a lightweight operating system where the time to compile is very low and it also allow remote debugging.

## Get xv6

xv6 is available at
```
https://pdos.csail.mit.edu/6.828/2018/xv6.html
```

Follow these commands to install Qemu and xv6
```
sudo apt-get install qemu
sudo apt-get install libc6-dev:i386
wget http://www.cse.iitd.ernet.in/~kumarsandeep/ta/ell405/assig1/
xv6-rev11.tar.gz --no-check-certificate
tar xzvf xv6-rev11.tar.gz
cd xv6-public
make
make qemu
```
## Add system Calls in xv6

In order to add a system call in xv6, following files should be modified to include the information of the system call to be added

* syscall.h
* syscall.c 
* user.h
* usys.s
* sysproc.c



## Run xv6
Enter the following commands to build the OS in the xv6 root di-
rectory:
```
make clean
make
```

If you want to test the user program, launch xv6 using the command
```
make qemu-nox
```
