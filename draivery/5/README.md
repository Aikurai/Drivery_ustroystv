┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ make clean
make
make -C /lib/modules/6.17.10+kali-amd64/build M=/home/kali/Zanyatiya/5 clean
make[1]: Entering directory '/usr/src/linux-headers-6.17.10+kali-amd64'
make[2]: Entering directory '/home/kali/Zanyatiya/5'
  CLEAN   Module.symvers
make[2]: Leaving directory '/home/kali/Zanyatiya/5'
make[1]: Leaving directory '/usr/src/linux-headers-6.17.10+kali-amd64'
make -C /lib/modules/6.17.10+kali-amd64/build M=/home/kali/Zanyatiya/5 modules
make[1]: Entering directory '/usr/src/linux-headers-6.17.10+kali-amd64'
make[2]: Entering directory '/home/kali/Zanyatiya/5'
  CC [M]  maipractice5driver.o
  MODPOST Module.symvers
  CC [M]  maipractice5driver.mod.o
  CC [M]  .module-common.o
  LD [M]  maipractice5driver.ko
  BTF [M] maipractice5driver.ko
make[2]: Leaving directory '/home/kali/Zanyatiya/5'
make[1]: Leaving directory '/usr/src/linux-headers-6.17.10+kali-amd64'
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ gcc -o rawexample rawexample.c
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ sudo insmod maipractice5driver.ko
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ lsmod | grep maipractice5
maipractice5driver     12288  0
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ sudo ./rawexample
Success!
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ dmesg | grep maipractice5driver

[ 7336.684570] maipractice5driver initialized
[ 7350.571997] maipractice5driver xmit
[ 7350.572000] maipractice5driver 000000006aca6440 struct skbuff
[ 7350.572001] maipractice5driver Packet info - Len 25, Head 000000008a25e834, Data 00000000d05e9398, Tail 27, End 384
[ 7350.572003] maipractice5driver First 25 bytes
[ 7350.572003] maipractice5driver Hex 00 12 34 56 78 90 00 00 00 00 00 00 12 34 68 65 6c 6c 6f 20 77 6f 72 6c 64 
[ 7350.572011] maipractice5driver Hex \x00 \x12 4 V x \x90 \x00 \x00 \x00 \x00 \x00 \x00 \x12 4 h e l l o   w o r l d 
[ 7386.227535] maipractice5driver removed
[ 7416.822594] maipractice5driver initialized
[ 7426.989249] maipractice5driver xmit
[ 7426.989251] maipractice5driver 00000000315b1403 struct skbuff
[ 7426.989253] maipractice5driver Packet info - Len 25, Head 000000000d030921, Data 000000004865439c, Tail 27, End 384
[ 7426.989254] maipractice5driver First 25 bytes
[ 7426.989255] maipractice5driver Hex 00 12 34 56 78 90 00 00 00 00 00 00 12 34 68 65 6c 6c 6f 20 77 6f 72 6c 64 
[ 7426.989261] maipractice5driver Hex \x00 \x12 4 V x \x90 \x00 \x00 \x00 \x00 \x00 \x00 \x12 4 h e l l o   w o r l d 
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ sudo rmmod maipractice5driver
                                                                           
┌──(kali㉿kali)-[~/Zanyatiya/5]
└─$ dmesg | tail -30
[ 6203.327190] 22:57:20.773789 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 6203.328287] 22:57:20.775350 dnd       No guest source window
[ 6203.346322] 22:57:20.792689 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 6203.347746] 22:57:20.794698 dnd       No guest source window
[ 6203.348884] 22:57:20.796029 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 6203.350265] 22:57:20.797244 dnd       No guest source window
[ 6203.358655] 22:57:20.806049 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 6203.359448] 22:57:20.806599 dnd       No guest source window
[ 6203.387096] 22:57:20.834328 dndHGCM   DnD: Received message HOST_DND_FN_GH_REQ_PENDING (0x258) from host
[ 6203.388448] 22:57:20.835498 dnd       No guest source window
[ 6924.558854] 23:09:22.043546 SHCLX11   Shared Clipboard: Converting VBox formats 'UNICODETEXT' to 'INVALID' for X11 (idxFmtX11=0, fmtX11=0, 
[ 6950.881978] 23:09:48.354724 SHCLX11   Shared Clipboard: Converting VBox formats 'UNICODETEXT' to 'INVALID' for X11 (idxFmtX11=0, fmtX11=0, 
[ 6994.507186] 23:10:31.958078 SHCLX11   Shared Clipboard: Converting VBox formats 'UNICODETEXT' to 'INVALID' for X11 (idxFmtX11=0, fmtX11=0, 
[ 7318.609951] 23:15:56.043727 SHCLX11   Shared Clipboard: Converting VBox formats 'UNICODETEXT' to 'INVALID' for X11 (idxFmtX11=0, fmtX11=0, 
[ 7336.684570] maipractice5driver initialized
[ 7350.571997] maipractice5driver xmit
[ 7350.572000] maipractice5driver 000000006aca6440 struct skbuff
[ 7350.572001] maipractice5driver Packet info - Len 25, Head 000000008a25e834, Data 00000000d05e9398, Tail 27, End 384
[ 7350.572003] maipractice5driver First 25 bytes
[ 7350.572003] maipractice5driver Hex 00 12 34 56 78 90 00 00 00 00 00 00 12 34 68 65 6c 6c 6f 20 77 6f 72 6c 64 
[ 7350.572011] maipractice5driver Hex \x00 \x12 4 V x \x90 \x00 \x00 \x00 \x00 \x00 \x00 \x12 4 h e l l o   w o r l d 
[ 7386.227535] maipractice5driver removed
[ 7416.822594] maipractice5driver initialized
[ 7426.989249] maipractice5driver xmit
[ 7426.989251] maipractice5driver 00000000315b1403 struct skbuff
[ 7426.989253] maipractice5driver Packet info - Len 25, Head 000000000d030921, Data 000000004865439c, Tail 27, End 384
[ 7426.989254] maipractice5driver First 25 bytes
[ 7426.989255] maipractice5driver Hex 00 12 34 56 78 90 00 00 00 00 00 00 12 34 68 65 6c 6c 6f 20 77 6f 72 6c 64 
[ 7426.989261] maipractice5driver Hex \x00 \x12 4 V x \x90 \x00 \x00 \x00 \x00 \x00 \x00 \x12 4 h e l l o   w o r l d 
[ 7437.992013] maipractice5driver removed
