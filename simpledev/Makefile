ifneq ($(KERNEL_RELEASE),)
	obj-m := simple.o
else
	KERNDIR ?= /home/peter/ws/linux-3.8.13/
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean
	rm *.o *.ko *.order *.symvers
