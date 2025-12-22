#ifndef DRIVER_IOCTL_H
#define DRIVER_IOCTL_H

#include <sys/ioctl.h>

#define MAGIC_NUM 100
#define DRIVER_CLEAR_BUF _IO(MAGIC_NUM, 0)
#define DRIVER_BUF_IS_EMPTY _IOR(MAGIC_NUM, 1, int)

#endif
