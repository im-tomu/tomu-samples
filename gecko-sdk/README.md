# Gecko SDK from SiLabs

This is the original Gecko SDK from Silicon Labs.

## Building

If the cross compiling toolchain is in your PATH then the Makefile will
auto-detect it; else (or to override it) specify it using the environment
variable "CROSS_COMPILE". There might be additional dependencies, depending
on which specific project you're using, and the instructions for compilation
are included in each project's README.md

1. Run `make deps .` to patch the linker with support for the Tomu and clone the [Gecko SDK](https://github.com/SiliconLabs/Gecko_SDK) locally.
1. Inside each project, run `make`.