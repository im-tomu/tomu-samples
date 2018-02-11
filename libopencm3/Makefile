all: libopencm3-examples
	@true

# libopencm3-examples includes libopencm3 as a git submodule
libopencm3-examples:
	git clone --depth 1 https://github.com/im-tomu/libopencm3-examples.git --branch efm32hg
	cd libopencm3-examples && git submodule init
	cd libopencm3-examples && git submodule update
	make -C libopencm3-examples
