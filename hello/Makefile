# Copyright 2016 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# Usee make V=1 for a verbose build.
ifndef V
        Q_CC		= @echo '      CC ' $@;
        Q_OBJDUMP	= @echo ' OBJDUMP ' $@;
        Q_OBJCOPY	= @echo ' OBJCOPY ' $@;
endif

################################################################################
#
# PATHS
#
# Put the path to the arm-none-eabi toolchain that you downloaded here, up to
# /bin/, and end with arm-none-eabi-
CROSS_COMPILE ?= arm-none-eabi-

# You can download the ARM toolchain from:
# https://launchpad.net/gcc-arm-embedded/+download

CC	= $(CROSS_COMPILE)gcc
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump

################################################################################
#
# ARGUMENTS TO COMPILERS/LINKERS
#
IFLAGS = -I. \
				 -I../Gecko_SDK/platform/CMSIS/Include \
				 -I../Gecko_SDK/platform/Device/SiliconLabs/EFM32HG/Include \
				 -I../Gecko_SDK/platform/emlib/inc \
				 -I../Gecko_SDK/hardware/kit/common/drivers

CFLAGS = $(IFLAGS) \
				 -DEFM32HG309F64 \
				 -Wall \
				 -Wextra \
				 -mcpu=cortex-m0plus \
				 -mthumb \
				 -ffunction-sections \
				 -fdata-sections \
				 -fomit-frame-pointer \
				 -std=c99 \
				 -MMD \
				 -MP \
				 -O0 \
				 -g

LSCRIPT = ../tomu.ld

LFLAGS = -mcpu=cortex-m0plus \
				 -mthumb \
				 -T$(LSCRIPT) \
				 --specs=nosys.specs \
				 -Wl,--gc-sections \
				 -Wl,--start-group \
				 -lnosys \
				 -Wl,--end-group


################################################################################
#
# PHONY TARGETS
#
.PHONY: all hello check clean

all: hello

hello: hello.bin hello.dump hello.elf

get_bootloader:
	[ ! -d ../an0042_efm32_usb_uart_bootloader_hg/bootld.bin ] && (cd ..; wget http://community.silabs.com/mgrfq63796/attachments/mgrfq63796/2/11213/1/an0042_efm32_usb_uart_bootloader_hg.zip; unzip an0042_efm32_usb_uart_bootloader_hg.zip;)
check:
	@echo "Checking Gecko SDK linker script $(LSCRIPT) to ensure FLASH ORIGIN is set to 0x00004000..."
	@grep -E '^\s*FLASH.*ORIGIN\s+=\s+0x' $(LSCRIPT)
	@grep -q -E '^\s*FLASH.*ORIGIN\s+=\s+0x0*4000' $(LSCRIPT) || exit 1
	@echo "Checking Gecko SDK linker script $(LSCRIPT) to ensure FLASH LENGTH is set to 0xC000..."
	@grep -E '^\s*FLASH.*LENGTH\s+=\s+0x' $(LSCRIPT)
	@grep -q -E '^\s*FLASH.*LENGTH\s+=\s+0x0*C000' $(LSCRIPT) || exit 1
	@echo "Checking Gecko SDK linker script $(LSCRIPT) to ensure RAM ORIGIN is set to 0x20000000..."
	@grep -E '^\s*RAM.*ORIGIN\s+=\s+0x' $(LSCRIPT)
	@grep -q -E '^\s*RAM.*ORIGIN\s+=\s+0x20000000' $(LSCRIPT) || exit 1
	@echo "Checking Gecko SDK linker script $(LSCRIPT) to ensure RAM LENGTH is set to 0x2000..."
	@grep -E '^\s*RAM.*LENGTH\s+=\s+0x' $(LSCRIPT)
	@grep -q -E '^\s*RAM.*LENGTH\s+=\s+0x0*2000' $(LSCRIPT) || exit 1
	@echo "Checking if bootloader is available..."
	@test -f ../an0042_efm32_usb_uart_bootloader_hg/bootld.bin
	@echo "Checking ARM Toolchain is installed and accessible..."
	@echo " -> GCC"
	@test -x $(CC) || exit 1
	@echo " -> OBJCOPY"
	@test -x $(OBJCOPY) || exit 1
	@echo " -> OBJDUMP"
	@test -x $(OBJDUMP) || exit 1
	@echo "All checks pass."

clean:
	@echo "Cleaning .bin files..."
	@rm -f *.bin
	@echo "Cleaning .dump files..."
	@rm -f *.dump
	@echo "Cleaning .d files..."
	@rm -f *.d
	@echo "Cleaning .elf files..."
	@rm -f *.elf
	@echo "Cleaning .map files..."
	@rm -f *.map
	@echo "Cleaning .o files..."
	@rm -f *.o


################################################################################
#
# REAL TARGETS // COMMON
#
GECKO_A_SRC = ../Gecko_SDK/platform/Device/SiliconLabs/EFM32HG/Source/GCC/startup_efm32hg.S
GECKO_C_SRC = $(shell [ -d ../Gecko_SDK ] && find ../Gecko_SDK/platform/emlib/src -name \*.c \! -name em_int.c) \
							../Gecko_SDK/platform/Device/SiliconLabs/EFM32HG/Source/system_efm32hg.c \
							../Gecko_SDK/hardware/kit/common/drivers/capsense.c
GECKO_OBJ = $(patsubst %.S,%.o,$(GECKO_A_SRC)) \
						$(patsubst %.c,%.o,$(GECKO_C_SRC))

%.o: %.c
	$(Q_CC)$(CC) -c $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(Q_CC)$(CC) -c $(CFLAGS) -c -o $@ $<


################################################################################
#
# REAL TARGETS // CLEAN
#
hello.dump: hello.elf
	$(Q_OBJDUMP)$(OBJDUMP) -Sx $^ > $@

hello.elf: main.o $(GECKO_OBJ)
	$(Q_CC)$(CC) -Xlinker -Map=hello.map $(LFLAGS) -o $@ $^

hello.bin: hello.elf
	$(Q_OBJCOPY)$(OBJCOPY) -O binary $< $@


hello-qemu.img: hello.bin
	#Copy 16k padding with NULLS
	rm -f $@
	dd if=../an0042_efm32_usb_uart_bootloader_hg/bootld.bin of=$@ ibs=16k obs=16k conv=sync
	cat hello.bin >> $@
