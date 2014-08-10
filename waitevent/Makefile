ifneq ($(KERNEL_RELEASE), )   #not equal 
	obj-m := waitevent.o
else
	obj-m := waitevent.o
	#KERNDIR ?= /usr/src/linux-headers-2.6.35-22-generic/
	KERNDIR ?= /usr/src/linux-headers-3.2.0-4-686-pae/
	PWD := 	$(shell pwd)
default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean

disclean:
	rm -rf  *.o 

