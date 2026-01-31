obj-m := pcd.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

CC := /opt/gcc-15/bin/gcc

all:
	$(MAKE) -C $(KDIR) M=$(PWD) CC=$(CC) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
