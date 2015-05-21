obj-m := crcheck.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)
#EXTRA_CFLAGS += -I$(src)/include

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) 

clean:
	rm -rf *.o *~ core *.ko *.mod.c .tmp_versions crcheck

test: 
	sudo insmod ./crcheck.ko
	sudo rmmod crcheck
	dmesg | tail
