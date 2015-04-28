#
# Copyright 2009 Nexell Co.
#	http://www.nexell.co.kr
#
obj-y += soc-reset.o soc-gpio.o
include  $(srctree)/drivers/platform/nexell/s5p6818/prototype.mk

PROTO_MODULE := drivers/platform/nexell/s5p6818/prototype/module
PROTO_BASE   := drivers/platform/nexell/s5p6818/prototype/base
KBUILD_CFLAGS += -I$(PROTO_MODULE) -I$(PROTO_BASE)

ifeq ($(CONFIG_S5P6818_PROTO_RELEASE),y)
KBUILD_CFLAGS += -D__LINUX__ -D__PRINTK__ -DNX_RELEASE
else
KBUILD_CFLAGS += -D__LINUX__ -D__PRINTK__ -DNX_DEBUG
endif
