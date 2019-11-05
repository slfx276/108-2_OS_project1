# Compile Linux Kernel

When we need to install another version of Linux kernel , or to add a system into kernel ,  
we can take below websites as references.

### Reference  type1 - Compile Kernel & add system call
[NTU-OS HW1](https://docs.google.com/presentation/d/1KwS9PuGZxLXQ9IEYJE7KUhnz3bHohJLWOH-CRGZkC40/edit#slide=id.p31)  
[Adding a System Call Which Can Pass a Userspace String](https://medium.com/@lee1003094395/adding-a-system-call-which-can-pass-a-userspace-string-b245105bed38?sk=acb214f7c1c08587efcdc644245e74c2&fbclid=IwAR0COzSo7NGzwHoEWOTkqjwYa48VYBCf5iAOutMMJjZCZO59zs75XRMrN9w)  
[Implementing a system call in Linux Kernel 4.7.1](https://medium.com/@ssreehari/implementing-a-system-call-in-linux-kernel-4-7-1-6f98250a8c38)  

### Reference type2 - Add kernel module
[寫一個簡單的 Linux Kernel Module](http://chriswenyuan.blogspot.com/2017/05/linux-kernel-module_4.html)  
<br>
<br>

if we don't need to make any change from kernel source , then just follow the steps below.

### 1. Setting up build environment
<pre><code>$ sudo apt-get update
$ sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc
$ sudo apt-get install libelf-dev
</code></pre>


### 2. Download the kernel source code from [The Linux Kernel Archives](https://www.kernel.org/)
or use  
<pre><code>$ wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.14.25.tar.xz</code></pre>
   
to download a "tar.xz" file , you can use any kernel version , this manual used to install **from 4.18.0-18 -> 4.14.25**


### 3. Extracting the archieve
<pre><code>$ tar Jxvf linux-4.14.25.tar.xz  
$ cd linux-4.14.25</code></pre>

### 4. Create .config file
.config file specify what kernel function we expect to use.

<pre><code>$ make menuconfig  // if you don's understand which to set, then just save to .congif
$ make olddefconfig // check compatability between new and old version kernels<code></pre>

### 5. Kernel Compilation
<pre><code>$ sudo make -j4 bzImage  // (編譯核心並壓縮)
$ sudo make -j4 modules  //(編譯各個核心模組)
$ sudo make modules_install  //(安裝模組)
$ sudo make install   //(安裝核心） 

$ sudo mkinitramfs -o /boot/initrd.img-4.14.25  // Do this whenever you reinstall the modules.
$ sudo update-initramfs -c -k 4.14.25  // 4.14.25 is the kernel version we want to use.
$ update-grub

$ sudo reboot
</code></pre>

-j4 means compile with 4 threads , which can speed up the compilation time.  
$ cat /proc/cpuinfo | grep processor | wc -l  // see the number of threads.


> after reboot , press "Esc" to enter grub for selecting kernel version. If you enter grub terminal , then command "exit" for exiting and then press "Esc" again to select **kernel-4.14.25 version.**









