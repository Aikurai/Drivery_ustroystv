#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../common/driver_ioctl.h"

static int write_to_dev(int fd, const char *data, size_t len) {
    ssize_t written = write(fd, data, len);
    if (written < 0) {
        perror("write failed");
        return -1;
    }
    printf("Written \"%s\" to dev\n", data);
    return 0;
}

static int read_from_dev(int fd, char *buf, size_t len) {
    ssize_t read_bytes = read(fd, buf, len);
    if (read_bytes < 0) {
        perror("read failed");
        return -1;
    }
    buf[read_bytes] = '\0';
    printf("read_from_dev: \"%s\"\n", buf);
    return 0;
}

int main(void) {
    const char *device = "/dev/mai_practice4_device";
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    int writer_fd = open(device, O_RDWR);
    if (writer_fd < 0) {
        perror("Failed to open device for writing");
        close(fd);
        return EXIT_FAILURE;
    }

    write_to_dev(writer_fd, "Hello from main", 15);

    char buf[256];
    read_from_dev(fd, buf, 10);

    int is_empty = 0;
    if (ioctl(fd, DRIVER_BUF_IS_EMPTY, &is_empty) < 0) {
        perror("ioctl DRIVER_BUF_IS_EMPTY failed");
        close(fd);
        close(writer_fd);
        return EXIT_FAILURE;
    }
    printf("Buffer is empty: %s\n", is_empty ? "true" : "false");

    if (ioctl(fd, DRIVER_CLEAR_BUF) < 0) {
        perror("ioctl DRIVER_CLEAR_BUF failed");
        close(fd);
        close(writer_fd);
        return EXIT_FAILURE;
    }

    if (ioctl(fd, DRIVER_BUF_IS_EMPTY, &is_empty) < 0) {
        perror("ioctl DRIVER_BUF_IS_EMPTY failed");
        close(fd);
        close(writer_fd);
        return EXIT_FAILURE;
    }
    printf("Buffer is empty after DRIVER_CLEAR_BUF: %s\n", is_empty ? "true" : "false");

    close(fd);
    close(writer_fd);

    return EXIT_SUCCESS;
}
