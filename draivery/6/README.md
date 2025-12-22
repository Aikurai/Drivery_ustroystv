# 1 Код
Задача:
- Написать PCI драйвер с `probe` и `release` для сетевого адаптера.
- Вставить в `probe` инициализацию сетевого драйвера с предидущего занятия.
- Реализовать чтение MAC адреса

У меня нет Ethernet порта, поэтому буду писать драйвер для wifi устройства `wlp0s20f3`.
Код драйвера находится в `mai_practice6_driver.c`.
# 2 Тестирование
Выключил устройство `wlp0s20f3` и выгрузил его драйвера:
```sh
sudo ip link set wlp0s20f3 down
sudo rmmod iwlmvm
sudo rmmod iwlwifi
```

Скомпилировал и вставил свой драйвер:
```sh
sudo insmod mai_practice6_driver.ko
```
`dmesg` показывает следующее:
```sh
[12516.408884] mai_practice6_driver: pci_driver_probe
[12516.409309] offset = 40
[12516.409320] MAC 70 3 0 0 d5 55 
[12516.409332] MAC 70 3 0 0 d5 55 
[12516.409339] MAC 70 3 0 0 d5 55 
[12516.409347] MAC 70 3 0 0 d5 55 
[12516.409354] MAC 70 3 0 0 d5 55 
[12516.409362] MAC 70 3 0 0 d5 55
[12516.457110] mai_practice6_driver: fake_net_dev_open
```

Скомпилировал и запустил тестовую программу с `practice5`:
```sh
$ sudo ./app
Success!
```
`dmesg` показывает следующее:
```sh
[12600.709322] mai_practice6_driver: xmit
[12600.709327] mai_practice6_driver: 00000000cf2d571c<struct sk_buff>
[12600.709330] mai_practice6_driver: Packet info - Len: 25, Head: 00000000be83f03a, Data: 000000002148b456, Tail: 27, End: 384
[12600.709332] mai_practice6_driver: First 25 bytes:
[12600.709332] mai_practice6_driver: Hex: 00 12 34 56 78 90 00 00 00 00 00 00 12 34 68 65 6c 6c 6f 20 77 6f 72 6c 64 
[12600.709343] mai_practice6_driver: Hex: \x00 \x12 4 V x \x90 \x00 \x00 \x00 \x00 \x00 \x00 \x12 4 h e l l o   w o r l d
```

Всё работает кроме реализации чтения MAC адреса. Эта реализация выдает:
```sh
[12516.409320] MAC 70 3 0 0 d5 55 
[12516.409332] MAC 70 3 0 0 d5 55 
[12516.409339] MAC 70 3 0 0 d5 55 
[12516.409347] MAC 70 3 0 0 d5 55 
[12516.409354] MAC 70 3 0 0 d5 55 
[12516.409362] MAC 70 3 0 0 d5 55
```
Но MAC адрес на самом деле выглядит так:
```sh
$ ip link show 
8: enp0s20f3: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UNKNOWN mode DEFAULT group default qlen 1000
    link/ether 00:00:00:00:00:00 brd ff:ff:ff:ff:ff:ff
```

Выгрузил свой драйвер:
```sh
$ sudo rmmod mai_practice6_driver
$ dmesg
[12775.464615] mai_practice6_driver: pci_driver_remove
[12775.464694] mai_practice6_driver: fake_net_dev_release
```

Загрузил обратно настоящие драйвера и включил `wlp0s20f3`:
```sh
sudo modprobe iwlwifi
sudo modprobe iwlmvm
sudo ip link set wlp0s20f3 up
```
