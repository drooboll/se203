PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
GDB = gdb-multiarch
EXE = main
SOURCES = $(wildcard *.c)
ASMSOURCES = $(wildcard *.s)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES)) $(patsubst %.s, %.o, $(ASMSOURCES))
DEPS = $(patsubst %.c, %.dep, $(SOURCES))
DIRS = -I CMSIS/Device/ST/STM32L4xx/Include -I CMSIS/Include

CFLAGS = -g -O1 -c -ffreestanding
TARGET_ARCH = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard
LDFLAGS = -T ld_ram.lds -nostartfiles -ffreestanding -nolibc
ASFLAGS = -g -c
TARGET_MACH = $(TARGET_ARCH)
LIBS = -lm

.PHONY: all debug gdbserver
all: $(EXE)

$(EXE): $(OBJECTS) image.o
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@ $(DIRS)
%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

%.dep : %.c
	$(CC) -MM $< -MF $@ $(DIRS)

image.o: image.raw
	$(OBJCOPY) -I binary -O elf32-littlearm --rename-section .data=.rodata $^ image.o

-include $(DEPS)

gdbserver:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) $(EXE)

clean:
	rm -f $(DEPS)
	rm -f $(OBJECTS)
	rm -f $(EXE)
