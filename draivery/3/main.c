// main.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    const char* const device_name = "/dev/mai_practice3_testdevice";
    int fd = open(device_name, O_RDWR | O_NONBLOCK);
    
    if (fd < 0) {
        perror("Failed to open device");
        printf("Error: %d\n", fd);
        return 1;
    }

    printf("Opened '%s' device with fd=%d\n", device_name, fd);
    close(fd);
    return 0;
}
