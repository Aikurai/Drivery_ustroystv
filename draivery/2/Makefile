obj-m := simple_char.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

install:
	sudo insmod simple_char.ko

uninstall:
	sudo rmmod simple_char.ko

check:
	@echo "=== Checking if module is loaded ==="
	lsmod | grep simple || echo "Module not loaded"
	@echo "=== dmesg output ==="
	dmesg | grep "mai 307" | tail -2
