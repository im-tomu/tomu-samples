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
