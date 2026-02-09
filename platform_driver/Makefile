obj-m := pcd_platform_driver.o
pcd_platform_driver-objs := pcd_device_setup.o

ARCH := arm
CROSS_COMPILE := arm-linux-gnueabihf-

KDIR := /home/hashmi/bbb-kernel/linux
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) \
	ARCH=$(ARCH) \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) \
	ARCH=$(ARCH) \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	M=$(PWD) clean
