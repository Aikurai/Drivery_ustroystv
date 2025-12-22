obj-m += maipractice5driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:
	sudo insmod maipractice5driver.ko

rmmod:
	sudo rmmod maipractice5driver.ko

dmesg:
	dmesg | tail -20
