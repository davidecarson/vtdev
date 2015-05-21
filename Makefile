obj-m += vmxinfo.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

vmxinfo:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) 

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test: 
	sudo insmod ./vmxinfo.ko
	sudo rmmod vmxinfo
	dmesg | tail