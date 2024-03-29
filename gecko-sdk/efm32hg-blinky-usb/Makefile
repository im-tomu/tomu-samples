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


# Use make V=1 for a verbose build.
ifndef V
        Q_CC		= @echo '      CC ' $@;
        Q_OBJDUMP	= @echo ' OBJDUMP ' $@;
        Q_OBJCOPY	= @echo ' OBJCOPY ' $@;
endif

# Define CROSS_COMPILE, CC, OBJCOPY and OBJDUMP
include ../paths.mk

################################################################################
#
# ARGUMENTS TO COMPILERS/LINKERS
#
IFLAGS = -I. \
				 -I../gecko_sdk/platform/CMSIS/Include \
				 -I../gecko_sdk/platform/Device/SiliconLabs/EFM32HG/Include \
				 -I../gecko_sdk/platform/emlib/inc \
				 -I../gecko_sdk/platform/middleware/usb_gecko/inc \
				 -I../gecko_sdk/hardware/kit/common/drivers

# Define CFLAGS, LSCRIPT and LFLAGS
include ../compile_flags.mk

################################################################################
#
# PHONY TARGETS
#
.PHONY: all blinky-usb check clean

all: blinky-usb

blinky-usb: blinky-usb.bin blinky-usb.dump blinky-usb.elf

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
GECKO_A_SRC = ../gecko_sdk/platform/Device/SiliconLabs/EFM32HG/Source/GCC/startup_efm32hg.S
GECKO_C_SRC = $(shell [ -d ../gecko_sdk ] && find ../gecko_sdk/platform/emlib/src ../gecko_sdk/platform/middleware/usb_gecko/src -name \*.c \! -name em_int.c ) \
							../gecko_sdk/platform/Device/SiliconLabs/EFM32HG/Source/system_efm32hg.c \
							../gecko_sdk/hardware/kit/common/drivers/capsense.c
GECKO_OBJ = $(patsubst %.S,%.o,$(GECKO_A_SRC)) \
						$(patsubst %.c,%.o,$(GECKO_C_SRC))

BLINKY_A_SRC = $(shell find . -maxdepth 1 -name \*.S)
BLINKY_C_SRC = $(shell find . -maxdepth 1 -name \*.c)
BLINKY_OBJ = $(patsubst %.S,%.o,$(BLINKY_A_SRC)) $(patsubst %.c,%.o,$(BLINKY_C_SRC))

%.o: %.c
	$(Q_CC)$(CC) -c $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(Q_CC)$(CC) -c $(CFLAGS) -c -o $@ $<


################################################################################
#
# REAL TARGETS // CLEAN
#
blinky-usb.dump: blinky-usb.elf
	$(Q_OBJDUMP)$(OBJDUMP) -Sx $^ > $@

blinky-usb.elf: $(BLINKY_OBJ) $(GECKO_OBJ)
	$(Q_CC)$(CC) -Xlinker -Map=blinky-usb.map $(LFLAGS) -o $@ $^

blinky-usb.bin: blinky-usb.elf
	$(Q_OBJCOPY)$(OBJCOPY) -O binary $< $@

