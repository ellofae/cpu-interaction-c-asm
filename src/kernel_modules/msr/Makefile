obj-m := msr_module.o

build_module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean_module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean