                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ make      
make -C /lib/modules/6.17.10+kali-amd64/build M=/home/kali/Zanyatiya/3 modules
make[1]: Entering directory '/usr/src/linux-headers-6.17.10+kali-amd64'
make[2]: Entering directory '/home/kali/Zanyatiya/3'
  CC [M]  mai_practice3_driver.o
  MODPOST Module.symvers
  CC [M]  mai_practice3_driver.mod.o
  CC [M]  .module-common.o
  LD [M]  mai_practice3_driver.ko
  BTF [M] mai_practice3_driver.ko
make[2]: Leaving directory '/home/kali/Zanyatiya/3'
make[1]: Leaving directory '/usr/src/linux-headers-6.17.10+kali-amd64'
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ sudo insmod mai_practice3_driver.ko

┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ sudo mknod /dev/mai_practice3_device c 243 0
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ sudo chmod 666 /dev/mai_practice3_device
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ ls -la /dev/mai_practice3_device
crw-rw-rw- 1 root root 243, 0 Dec 20 17:31 /dev/mai_practice3_device

┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ sudo insmod mai_practice3_driver.ko

┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ gcc -o app app.c
sudo ./app
Opened '/dev/mai_practice3_device' device with fd=3
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/3]
└─$ dmesg | tail -10                             
[ 4568.664152] 22:30:06.113815 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 4568.664653] 22:30:06.114370 dnd       No guest source window
[ 4568.674180] 22:30:06.123655 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 4568.675425] 22:30:06.124726 dnd       No guest source window
[ 4666.334560] Trying to initialize the driver
[ 4666.334563] Successfully initialized the driver
[ 4683.167314] mai_practice3_device: trying to open the device
[ 4683.167363] mai_practice3_device: trying to release the device
[ 4694.487875] mai_practice3_device: trying to open the device
