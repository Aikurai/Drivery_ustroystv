┌──(kali㉿kali)-[~/Zanyatiya/4]
└─$ cd driver
make

make -C /lib/modules/6.17.10+kali-amd64/build M=/home/kali/Zanyatiya/4/driver modules
make[1]: Entering directory '/usr/src/linux-headers-6.17.10+kali-amd64'
make[2]: Entering directory '/home/kali/Zanyatiya/4/driver'
  CC [M]  mai_practice4_driver.o
  MODPOST Module.symvers
  CC [M]  mai_practice4_driver.mod.o
  CC [M]  .module-common.o
  LD [M]  mai_practice4_driver.ko
  BTF [M] mai_practice4_driver.ko
make[2]: Leaving directory '/home/kali/Zanyatiya/4/driver'
make[1]: Leaving directory '/usr/src/linux-headers-6.17.10+kali-amd64'
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/4/driver]
└─$ sudo insmod mai_practice4_driver.ko
dmesg | grep mai_practice4_device

[ 5432.430767] mai_practice4_device: trying to initialize the driver
[ 5432.431485] mai_practice4_device: successfully initialized the driver
[ 6014.317431] mai_practice4_device: device_open: trying to open the device
[ 6014.317437] mai_practice4_device: device_open: trying to open the device
[ 6014.317438] mai_practice4_device: device_write: count=15, offset=0, buffer_len=0
[ 6014.317439] mai_practice4_device: device_write: successfully wrote 15 bytes
[ 6014.317492] mai_practice4_device: device_read: count=10, offset=0, buffer_len=15
[ 6014.317493] mai_practice4_device: device_read: successfully read 10 bytes
[ 6014.317496] mai_practice4_device: device_ioctl: cmd=0x80046401
[ 6014.317496] mai_practice4_device: device_ioctl: DRIVER_BUF_IS_EMPTY
[ 6014.317497] mai_practice4_device: device_ioctl: cmd=0x6400
[ 6014.317498] mai_practice4_device: device_ioctl: DRIVER_CLEAR_BUF
[ 6014.317499] mai_practice4_device: device_ioctl: cmd=0x80046401
[ 6014.317499] mai_practice4_device: device_ioctl: DRIVER_BUF_IS_EMPTY
[ 6014.317501] mai_practice4_device: device_release: trying to release the device
[ 6014.317503] mai_practice4_device: device_release: trying to release the device
[ 6076.888600] mai_practice4_device: driver unloaded
[ 6158.808623] mai_practice4_device: trying to initialize the driver
[ 6158.810051] mai_practice4_device: successfully initialized the driver
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/4/driver]
└─$ cd ../app
make

gcc -Wall -Wextra -o main main.c
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/4/app]
└─$ sudo ./main

Written "Hello from main" to dev
read_from_dev: "Hello from"
Buffer is empty: false
Buffer is empty after DRIVER_CLEAR_BUF: true
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/4/app]
└─$ dmesg | tail -30

[ 6014.317437] mai_practice4_device: device_open: trying to open the device
[ 6014.317438] mai_practice4_device: device_write: count=15, offset=0, buffer_len=0
[ 6014.317439] mai_practice4_device: device_write: successfully wrote 15 bytes
[ 6014.317492] mai_practice4_device: device_read: count=10, offset=0, buffer_len=15
[ 6014.317493] mai_practice4_device: device_read: successfully read 10 bytes
[ 6014.317496] mai_practice4_device: device_ioctl: cmd=0x80046401
[ 6014.317496] mai_practice4_device: device_ioctl: DRIVER_BUF_IS_EMPTY
[ 6014.317497] mai_practice4_device: device_ioctl: cmd=0x6400
[ 6014.317498] mai_practice4_device: device_ioctl: DRIVER_CLEAR_BUF
[ 6014.317499] mai_practice4_device: device_ioctl: cmd=0x80046401
[ 6014.317499] mai_practice4_device: device_ioctl: DRIVER_BUF_IS_EMPTY
[ 6014.317501] mai_practice4_device: device_release: trying to release the device
[ 6014.317503] mai_practice4_device: device_release: trying to release the device
[ 6076.888600] mai_practice4_device: driver unloaded
[ 6158.808623] mai_practice4_device: trying to initialize the driver
[ 6158.810051] mai_practice4_device: successfully initialized the driver
[ 6173.404353] mai_practice4_device: device_open: trying to open the device
[ 6173.404357] mai_practice4_device: device_open: trying to open the device
[ 6173.404358] mai_practice4_device: device_write: count=15, offset=0, buffer_len=0
[ 6173.404359] mai_practice4_device: device_write: successfully wrote 15 bytes
[ 6173.404403] mai_practice4_device: device_read: count=10, offset=0, buffer_len=15
[ 6173.404404] mai_practice4_device: device_read: successfully read 10 bytes
[ 6173.404406] mai_practice4_device: device_ioctl: cmd=0x80046401
[ 6173.404407] mai_practice4_device: device_ioctl: DRIVER_BUF_IS_EMPTY
[ 6173.404408] mai_practice4_device: device_ioctl: cmd=0x6400
[ 6173.404409] mai_practice4_device: device_ioctl: DRIVER_CLEAR_BUF
[ 6173.404409] mai_practice4_device: device_ioctl: cmd=0x80046401
[ 6173.404410] mai_practice4_device: device_ioctl: DRIVER_BUF_IS_EMPTY
[ 6173.404412] mai_practice4_device: device_release: trying to release the device
[ 6173.404413] mai_practice4_device: device_release: trying to release the device
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/4/app]
└─$ sudo rmmod mai_practice4_driver.ko

                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/4/app]
└─$ cd ../driver && make clean
cd ../app && make clean

make -C /lib/modules/6.17.10+kali-amd64/build M=/home/kali/Zanyatiya/4/driver clean
make[1]: Entering directory '/usr/src/linux-headers-6.17.10+kali-amd64'
make[2]: Entering directory '/home/kali/Zanyatiya/4/driver'
  CLEAN   Module.symvers
make[2]: Leaving directory '/home/kali/Zanyatiya/4/driver'
make[1]: Leaving directory '/usr/src/linux-headers-6.17.10+kali-amd64'
rm -f main
