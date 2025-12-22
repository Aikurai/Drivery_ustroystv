┌──(kali㉿kali)-[~/Zanyatiya/2]
└─$ make      
make -C /lib/modules/6.17.10+kali-amd64/build M=/home/kali/Zanyatiya/2 modules
make[1]: Entering directory '/usr/src/linux-headers-6.17.10+kali-amd64'
make[2]: Entering directory '/home/kali/Zanyatiya/2'
  CC [M]  simple_char.o
  MODPOST Module.symvers
  CC [M]  simple_char.mod.o
  CC [M]  .module-common.o
  LD [M]  simple_char.ko
  BTF [M] simple_char.ko
make[2]: Leaving directory '/home/kali/Zanyatiya/2'
make[1]: Leaving directory '/usr/src/linux-headers-6.17.10+kali-amd64'
                                                                            
┌──(kali㉿kali)-[~/Zanyatiya/2]
└─$ make install
sudo insmod simple_char.ko
                                                                            
┌──(kali㉿kali)-[~/Zanyatiya/2]
└─$ make check  
=== Checking if module is loaded ===
lsmod | grep simple || echo "Module not loaded"
simple_char            12288  0
=== dmesg output ===
dmesg | grep "mai 307" | tail -2
tail: option used in invalid context -- 2
make: *** [Makefile:22: check] Error 1
                                                                            
┌──(kali㉿kali)-[~/Zanyatiya/2]
└─$ make uninstall  
sudo rmmod simple_char.ko
