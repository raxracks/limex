# This is a Makefile meant for GNU Make. Assert that.
ifneq (,)
This makefile requires GNU Make.
endif

# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := limux.elf

# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
ifeq ($(origin CC), default)
CC := x86_64-linux-gnu-gcc
endif

ASM := nasm

# Likewise, "ld" here is just a placeholder and your mileage may vary if using the
# host's "ld".
ifeq ($(origin LD), default)
LD := x86_64-linux-gnu-ld
endif

# User controllable CFLAGS.
CFLAGS ?= -Wall -Wextra -O2 -pipe -Werror
ASMFLAGS ?= -felf64

# User controllable linker flags. We set none by default.
LDFLAGS ?=

# Internal C flags that should not be changed by the user.
override INTERNALCFLAGS :=   \
	-Iincludes           \
	-std=gnu11           \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-pic             \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD

# Internal linker flags that should not be changed by the user.
override INTERNALLDFLAGS :=    \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static

# Use find to glob all *.c files in the directory and extract the object names.
override CFILES := $(shell find ./src/ -type f -name '*.c')
override ASMFILES := $(shell find ./src/ -type f -name '*.asm')
override OBJ := $(CFILES:.c=.o)
override ASMOBJ := $(ASMFILES:.asm=.o)
override HEADER_DEPS := $(CFILES:.c=.d)

# Default target.
.PHONY: all
all: $(KERNEL)

includes/stivale2.h:
	curl https://raw.githubusercontent.com/stivale/stivale/master/stivale2.h -o $@

# Link rules for the final kernel executable.
$(KERNEL): $(OBJ) $(ASMOBJ)
	$(LD) $(OBJ) $(ASMOBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@
	rm -rf $(OBJ) $(HEADER_DEPS)

# Compilation rules for *.c files.
-include $(HEADER_DEPS)
%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f includes/stivale2.h
