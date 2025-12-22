Задание:
1. Добавить драйвер из предыдущей работы в kernel чтобы драйвер был виден в `make menuconfig`;
2. Создать патч;

# Ход работы
Склонировал linux:
```sh
git clone --depth 1 --branch v6.17 https://github.com/torvalds/linux.git
```

Скопирован драйвер из `practice6` в `drivers/net/ethernet`:
```sh
cd linux/drivers/net
cp ../../../mai-drivers/practice6 ethernet/mai_driver -r
```

Изменённые файлы:
```sh
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	modified:   drivers/net/ethernet/Kconfig
	modified:   drivers/net/ethernet/Makefile
	new file:   drivers/net/ethernet/mai_driver/Kconfig
	new file:   drivers/net/ethernet/mai_driver/Makefile
	new file:   drivers/net/ethernet/mai_driver/mai_practice6_driver.c
```

Добавлен файл `drivers/net/ethernet/mai_driver/Kconfig`:
```sh
config MAI_DRIVER
        tristate "MAI driver"
        depends on PCI
        help
          This is the MAI driver for practice7.
```

Добавлен файл `drivers/net/ethernet/mai_driver/Makefile`:
```sh
obj-$(CONFIG_MAI_DRIVER) += mai_practice6_driver.o
```

Изменения произведенные в уже существующих файлах (`my_changes.patch`):
```
diff --git a/drivers/net/ethernet/Kconfig b/drivers/net/ethernet/Kconfig
index f86d4557d..76901e313 100644
--- a/drivers/net/ethernet/Kconfig
+++ b/drivers/net/ethernet/Kconfig
@@ -203,4 +203,6 @@ source "drivers/net/ethernet/wiznet/Kconfig"
 source "drivers/net/ethernet/xilinx/Kconfig"
 source "drivers/net/ethernet/xircom/Kconfig"
 
+source "drivers/net/ethernet/mai_driver/Kconfig"
+
 endif # ETHERNET
diff --git a/drivers/net/ethernet/Makefile b/drivers/net/ethernet/Makefile
index 671823394..f3c581553 100644
--- a/drivers/net/ethernet/Makefile
+++ b/drivers/net/ethernet/Makefile
@@ -3,6 +3,7 @@
 # Makefile for the Linux network Ethernet device drivers.
 #
 
+obj-$(CONFIG_MAI_DRIVER) += mai_driver/
 obj-$(CONFIG_NET_VENDOR_3COM) += 3com/
 obj-$(CONFIG_NET_VENDOR_8390) += 8390/
 obj-$(CONFIG_NET_VENDOR_ACTIONS) += actions/

```

При выполнении `make menuconfig` (MAI драйвер в самом конце):
```
  ┌───────────────────────────────────────── Ethernet driver support ─────────────────────────────────────────┐
  │  Arrow keys navigate the menu.  <Enter> selects submenus ---> (or empty submenus ----).  Highlighted      │  
  │  letters are hotkeys.  Pressing <Y> includes, <N> excludes, <M> modularizes features.  Press <Esc><Esc>   │  
  │  to exit, <?> for Help, </> for Search.  Legend: [*] built-in  [ ] excluded  <M> module  < > module       │  
  │  capable                                                                                                  │  
  │ ┌────────────────^(-)───────────────────────────────────────────────────────────────────────────────────┐ │  
  │ │                <M>     TI ThunderLAN support                                                          │ │  
  │ │                [*]   Vertexcom devices                                                                │ │  
  │ │                <M>     Vertexcom MSE102x SPI                                                          │ │  
  │ │                [*]   VIA devices                                                                      │ │  
  │ │                <M>     VIA Rhine support                                                              │ │  
  │ │                [*]       Use MMIO instead of PIO                                                      │ │  
  │ │                <M>     VIA Velocity support                                                           │ │  
  │ │                [*]   Wangxun devices                                                                  │ │  
  │ │                <M>     Wangxun(R) GbE PCI Express adapters support                                    │ │  
  │ │                <M>     Wangxun(R) 10/25/40GbE PCI Express adapters support                            │ │  
  │ │                < >     Wangxun(R) 10/25/40G Virtual Function Ethernet support (NEW)                   │ │  
  │ │                < >     Wangxun(R) GbE Virtual Function Ethernet support (NEW)                         │ │  
  │ │                [*]   WIZnet devices                                                                   │ │  
  │ │                <M>     WIZnet W5100 Ethernet support                                                  │ │  
  │ │                <M>     WIZnet W5300 Ethernet support                                                  │ │  
  │ │                        WIZnet interface mode (Select interface mode in runtime)  --->                 │ │  
  │ │                <M>     WIZnet W5100/W5200/W5500 Ethernet support for SPI mode                         │ │  
  │ │                [*]   Xilinx devices                                                                   │ │  
  │ │                <M>     Xilinx 10/100 Ethernet Lite support                                            │ │  
  │ │                <M>     Xilinx 10/100/1000 AXI Ethernet support                                        │ │  
  │ │                <M>     Xilinx LL TEMAC (LocalLink Tri-mode Ethernet MAC) driver                       │ │  
  │ │                [*]   Xircom devices                                                                   │ │  
  │ │                <M>     Xircom 16-bit PCMCIA support                                                   │ │  
  │ │                < >   MAI driver (NEW)                                                                 │ │  
  │ └───────────────────────────────────────────────────────────────────────────────────────────────────────┘ │  
  ├───────────────────────────────────────────────────────────────────────────────────────────────────────────┤  
  │                         <Select>    < Exit >    < Help >    < Save >    < Load >                          │  
  └───────────────────────────────────────────────────────────────────────────────────────────────────────────┘  
```