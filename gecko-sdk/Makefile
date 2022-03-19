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

################################################################################
#
# Gecko
#
LSCRIPT = tomu.ld
GECKO_SDK_REV = v4.0.2

################################################################################
#
# PHONY TARGETS
#
.PHONY: all blinky check clean deps

all:
	make -C efm32hg-blinky
	make -C efm32hg-blinky-usb

clean:
	make -C efm32hg-blinky clean
	make -C efm32hg-blinky-usb clean
	@echo "Cleaning gecko_sdk files..."
	@find gecko_sdk -type f -name \*.bin -delete
	@find gecko_sdk -type f -name \*.dump -delete
	@find gecko_sdk -type f -name \*.d -delete
	@find gecko_sdk -type f -name \*.elf -delete
	@find gecko_sdk -type f -name \*.map -delete
	@find gecko_sdk -type f -name \*.o -delete


dist-clean:
	make clean || true
	rm -rf gecko_sdk
	rm tomu.ld

deps:
	@if [ ! -d gecko_sdk ]; then \
		git clone --depth 1 https://github.com/SiliconLabs/gecko_sdk --branch ${GECKO_SDK_REV}; \
	fi
	@if [ ! -f "${LSCRIPT}" ]; then \
		echo "Patching linker file to ${LSCRIPT}"; \
		patch -o ${LSCRIPT} gecko_sdk/platform/Device/SiliconLabs/EFM32HG/Source/GCC/efm32hg.ld linker.patch; \
	fi

