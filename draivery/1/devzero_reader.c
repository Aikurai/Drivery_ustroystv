#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int fd;
    void *buf;
    
    fd = open("/dev/zero", O_RDONLY);
    if (fd == -1) {
        exit(1);
    }
    
    buf = mmap(NULL, 4096, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == MAP_FAILED) {
        close(fd);
        exit(1);
    }
    
    read(fd, buf, 4096);
    
    munmap(buf, 4096);
    close(fd);
    
    return 0;
}