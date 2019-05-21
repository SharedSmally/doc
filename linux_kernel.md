## [Kernel](https://www.kernel.org/)

- [Compile Linux Kernel](https://www.cyberciti.biz/tips/compiling-linux-kernel-26.html)


- makefile
```
KERNEL_MAJOR=5
KERNEL_VERSION=${KERNEL_MAJOR}.1.3


FILE=linux-${KERNEL_VERSION}.tar.xz
URL=https://cdn.kernel.org/pub/linux/kernel/v${KERNEL_MAJOR}.x/linux-${KERNEL_VERSION}.tar.xz
SIG=https://cdn.kernel.org/pub/linux/kernel/v${KERNEL_MAJOR}.x/linux-${KERNEL_VERSION}.tar.sig

main: src/${FILE}
        gpg --verify $SIG
        xz -d -v $<
        tar xvf linux-${KERNEL_VERSION}.tar
        cd linux-${KERNEL_VERSION} && cp -v /boot/config-$(uname -r) .config
         make menuconfig

src/${FILE}:
        wget ${URL} -O $@

```
