# Задание
В наш pci драйвер добавить атрибут чтобы читать адрес области ввода/вывода

# Ход работы
Скопировал pci драйвер из `practice6`.

Выключил устройство `wlp0s20f3` и выгрузил его драйвера:
```sh
$ sudo ip link set wlp0s20f3 down
$ sudo rmmod iwlmvm
$ sudo rmmod iwlwifi
```

Скомпилировал и вставил свой драйвер:
```sh
$ sudo insmod mai_practice8_driver.ko
```

`dmesg` показывает следующее:
```sh
[15184.130118] mai_practice8_driver: pci_driver_probe
[15184.130514] offset = 40
[15184.130525] MAC 70 3 0 0 d5 55 
[15184.130536] MAC 70 3 0 0 d5 55 
[15184.130544] MAC 70 3 0 0 d5 55 
[15184.130551] MAC 70 3 0 0 d5 55 
[15184.130558] MAC 70 3 0 0 d5 55 
[15184.130566] MAC 70 3 0 0 d5 55
[15184.153372] mai_practice8_driver 0000:00:14.3 enp0s20f3: renamed from eth0
[15184.182091] mai_practice8_driver: fake_net_dev_open
```

Нашёл файл с помощью команды `find`:
```sh
$ sudo find /sys -name "io_address" -type f
/sys/devices/pci0000:00/0000:00:14.3/io_address
```

Несколько раз вызвал функцию `show` с помощью команды `cat`:
```sh
$ cat /sys/devices/pci0000:00/0000:00:14.3/io_address
Pci resource start address: 600113c000
Pci resource length: 16384
Mapped address: 00000000d439cab9
$ cat /sys/devices/pci0000:00/0000:00:14.3/io_address
Pci resource start address: 600113c000
Pci resource length: 16384
Mapped address: 00000000d1db0ebd
$ cat /sys/devices/pci0000:00/0000:00:14.3/io_address
Pci resource start address: 600113c000
Pci resource length: 16384
Mapped address: 0000000034e6891b
```

Выгрузил свой драйвер:
```sh
$ sudo rmmod mai_practice8_driver
$ dmesg
[15682.067645] mai_practice8_driver: pci_driver_remove
[15682.067685] mai_practice8_driver: fake_net_dev_release
```

Загрузил обратно настоящие драйвера и включил `wlp0s20f3`:
```sh
$ sudo modprobe iwlwifi
$ sudo modprobe iwlmvm
$ sudo ip link set wlp0s20f3 up
```
