# 1. Написать программу для чтения данных с устройства /dev/zero:

```c

#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <unistd.h>

#include <sys/mman.h>



int main() {

    int fd;

    void \*buf;

    

    fd = open("/dev/zero", O\_RDONLY);

    if (fd == -1) {

        exit(1);

    }

    

    buf = mmap(NULL, 4096, PROT\_READ, MAP\_PRIVATE, fd, 0);

    if (buf == MAP\_FAILED) {

        close(fd);

        exit(1);

    }

    

    read(fd, buf, 4096);

    

    munmap(buf, 4096);

    close(fd);

    

    return 0;

}}

```

makefile:

```makefile

CC=gcc

CFLAGS=-Wall -Wextra -std=c11 -O2

TARGET=devzero\_reader



all: $(TARGET)



$(TARGET): devzero\_reader.c

 	$(CC) $(CFLAGS) -o $(TARGET) devzero\_reader.c



clean:

 	rm -f $(TARGET)



.PHONY: all clean

```



# 2. При помощи strace найти системные вызовы для работы с файловой и подсистемой работы с памятью

```sh

┌──(kali㉿kali)-\[/media/sf\_Desktop/Drivery\_Ustroystv/1]

└─$ strace -e trace=file,mmap,memory ./devzero\_reader  

execve("./devzero\_reader", \["./devzero\_reader"], 0x7ffeadc7b120 /\* 55 vars \*/) = 0

brk(NULL)                               = 0x561b5844d000

mmap(NULL, 8192, PROT\_READ|PROT\_WRITE, MAP\_PRIVATE|MAP\_ANONYMOUS, -1, 0) = 0x7fcd60f64000

access("/etc/ld.so.preload", R\_OK)      = -1 ENOENT (No such file or directory)

openat(AT\_FDCWD, "/etc/ld.so.cache", O\_RDONLY|O\_CLOEXEC) = 3

mmap(NULL, 93279, PROT\_READ, MAP\_PRIVATE, 3, 0) = 0x7fcd60f4d000

openat(AT\_FDCWD, "/lib/x86\_64-linux-gnu/libc.so.6", O\_RDONLY|O\_CLOEXEC) = 3

mmap(NULL, 2055800, PROT\_READ, MAP\_PRIVATE|MAP\_DENYWRITE, 3, 0) = 0x7fcd60d57000

mmap(0x7fcd60d7f000, 1462272, PROT\_READ|PROT\_EXEC, MAP\_PRIVATE|MAP\_FIXED|MAP\_DENYWRITE, 3, 0x28000) = 0x7fcd60d7f000

mmap(0x7fcd60ee4000, 352256, PROT\_READ, MAP\_PRIVATE|MAP\_FIXED|MAP\_DENYWRITE, 3, 0x18d000) = 0x7fcd60ee4000

mmap(0x7fcd60f3a000, 24576, PROT\_READ|PROT\_WRITE, MAP\_PRIVATE|MAP\_FIXED|MAP\_DENYWRITE, 3, 0x1e2000) = 0x7fcd60f3a000

mmap(0x7fcd60f40000, 52856, PROT\_READ|PROT\_WRITE, MAP\_PRIVATE|MAP\_FIXED|MAP\_ANONYMOUS, -1, 0) = 0x7fcd60f40000

mmap(NULL, 12288, PROT\_READ|PROT\_WRITE, MAP\_PRIVATE|MAP\_ANONYMOUS, -1, 0) = 0x7fcd60d54000

mprotect(0x7fcd60f3a000, 16384, PROT\_READ) = 0

mprotect(0x561b33619000, 4096, PROT\_READ) = 0

mprotect(0x7fcd60fa0000, 8192, PROT\_READ) = 0

munmap(0x7fcd60f4d000, 93279)           = 0

openat(AT\_FDCWD, "/dev/zero", O\_RDONLY) = 3

mmap(NULL, 4096, PROT\_READ, MAP\_PRIVATE, 3, 0) = 0x7fcd60f63000

munmap(0x7fcd60f63000, 4096)            = 0

+++ exited with 0 +++

```



Системные вызовы: `read`, `close`, nmap`, `close`, `munmap`

# 3. Найти системные вызовы в исходниках ядра 6.12.58



Найдём системные вызовы `read`, `close`, nmap`, `close`, `munmap` в исходниках ядра.



## read 

```c

user: read(fd, buf, 4096)

 syscall #0

SYSCALL\_DEFINE3(read) \[fs/read\_write.c:595]

   ksys\_read(fd, buf, count) \[fs/read\_write.c:382]

       fget(fd) → struct file \*file

       vfs\_read(file, buf, count, \&pos) \[fs/read\_write.c:534]

           file->f\_op->read(file, buf, count, \&pos)

                 zero\_read(file, buf, count, pos) \[fs/char\_dev.c:47]

                     memset\_user(buf, 0, count) ← заполняет нулями

                     return count

```



## close 

```c

user: close(fd)

 syscall #3

SYSCALL\_DEFINE1(close) \[fs/close.c:22]

     \_\_close\_fd(current->files, fd) \[fs/file.c:2150]

         files\_lock() ← блокировка таблицы файлов

         fcheck\_files(files, fd) → struct file \*file

         \_\_fput(file) \[fs/file\_table.c:350]

             file->f\_op->release()

             fput\_many(files, idx)

```



## nmap

```c

user: mmap(NULL, 4096, PROT\_READ, MAP\_PRIVATE, fd, 0)

 syscall #9

SYSCALL\_DEFINE6(mmap\_pgoff) \[mm/mmap.c:614]

     ksys\_mmap\_pgoff(addr, len, prot, flags, fd, pgoff) \[mm/mmap.c:585]

         vm\_mmap\_pgoff(file, addr, len, prot, flags, pgoff) \[mm/util.c:133]

             mmap\_lock(mm) ← блокировка адресного пространства

             do\_mmap(file, addr, len, prot, flags, pgoff, 0) \[mm/mmap.c:173]

                 addr = get\_unmapped\_area(file, addr, len, pgoff, flags)

                 addr = mmap\_region(file, addr, len, vm\_flags, pgoff) \[mm/mmap.c:553]

                     file->f\_op->mmap(file, vma) 

                         memory\_mmap(file, vma) \[drivers/char/mem.c:1085]

                             zeromap\_page\_range(vma, 0, len, zero\_pfn) ← VM\_ZERO\_FILL

```



## munmap

```c

user: munmap(addr, 4096)

 syscall #11

SYSCALL\_DEFINE2(munmap) \[mm/mmap.c:648]

     vm\_munmap(addr, len) \[mm/util.c:179]

         mmap\_lock\_killable(mm) ← блокировка

         do\_munmap(mm, addr, len, 0) \[mm/mmap.c:746]

             detach\_vmas\_to\_be\_unmapped(mm, vma, prev, end) \[mm/mmap.c:2616]

             unmap\_single\_vma(mm, vma, start, end, 0) \[mm/mmap.c:2236]

                 zap\_page\_range(vma, start, size)

                 remove\_vma(mm, vma)

             exit\_mmap(mm) 


```
