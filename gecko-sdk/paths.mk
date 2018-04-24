################################################################################
#
# PATHS
#
# Put the full path to the arm-none-eabi-gcc binary here, without
# the trailing "gcc"
# E.g. CROSS_COMPILE = /bin/arm-none-eabi-
CROSS_COMPILE ?= $(patsubst %gcc,%,$(shell which arm-none-eabi-gcc))

# You can download the ARM toolchain from:
# https://launchpad.net/gcc-arm-embedded/+download

CC	= $(CROSS_COMPILE)gcc
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump
