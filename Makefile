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
CROSS_COMPILE ?= $(patsubst %gcc,%,$(shell which arm-none-eabi-gcc))


# You can download the ARM toolchain from:
# https://launchpad.net/gcc-arm-embedded/+download

CC	= $(CROSS_COMPILE)gcc
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump

################################################################################
#
# Gecko
#
LSCRIPT = tomu.ld
GECKO_SDK_REV = v5.0.0

################################################################################
#
# PHONY TARGETS
#
.PHONY: all blinky check clean deps

all:
	make -C efm32hg-blinky
	make -C efm32hg-blinky+usb

clean:
	make -C efm32hg-blinky clean
	make -C efm32hg-blinky+usb clean
	@echo "Cleaning Gecko_SDK files..."
	@find Gecko_SDK -type f -name \*.bin -delete
	@find Gecko_SDK -type f -name \*.dump -delete
	@find Gecko_SDK -type f -name \*.d -delete
	@find Gecko_SDK -type f -name \*.elf -delete
	@find Gecko_SDK -type f -name \*.map -delete
	@find Gecko_SDK -type f -name \*.o -delete


dist-clean:
	make clean || true
	rm -rf Gecko_SDK
	rm tomu.ld

deps:
	@if [ ! -d Gecko_SDK ]; then \
		git clone --depth 1 https://github.com/SiliconLabs/Gecko_SDK --branch ${GECKO_SDK_REV}; \
	fi
	@if [ ! -f "${LSCRIPT}" ]; then \
		echo "Patching linker file to ${LSCRIPT}"; \
		patch -o ${LSCRIPT} Gecko_SDK/platform/Device/SiliconLabs/EFM32HG/Source/GCC/efm32hg.ld linker.patch; \
	fi

