# tomu-samples

## What are these:

These projects are simple programs for the [Tomu](http://tomu.im). They do
various things, and are intended to offer code examples and simple testing to
ease your introduction to the Tomu platform.

## How to use:

1. To compile these, you'll need a cross-compiling toolchain to arm-none-eabi.

  - Debian/Ubuntu/... : `sudo apt-get install gcc-arm-none-eabi`
  - Fedora : `sudo yum install arm-none-eabi-gcc-cs`
  - Arch : `sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib`
  - Other Linux : check your package manager, or
  - Anything else (Windows, OSX, Linux) : [https://launchpad.net/gcc-arm-embedded/+download](https://launchpad.net/gcc-arm-embedded/+download)

  If the cross compiling toolchain is in your PATH then the Makefile will
  auto-detect it; else (or to override it) specify it using the environment
  variable "CROSS_COMPILE".
  There might be additional dependencies, depending on which specific project
  you're using, and the instructions for compilation are included in each
  project's README.md
2. Run `make deps .` to patch the linker with support for the Tomu and clone the [Gecko SDK](https://github.com/SiliconLabs/Gecko_SDK) locally
3. Now you can build the examples

## Flashing:

Once you've compiled the code, you can flash the Tomu using `minicom` on linux
and OSX, or some other serial I/O utility on Windows. To do that, set it up with
`115200 8n1`, then use `i` to show the bootloader version.

To upload the binary, press `u`, wait till the bootloader replies with `Ready`,
then press `^A-S`, choose XMODEM, choose the `.bin` file produced by the
compilation, and wait until it's uploaded.

Once that's done, press `b` to boot into the firmware. The bootloader will hang
for 5-7 seconds, then the Tomu will boot.
