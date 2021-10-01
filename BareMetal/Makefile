PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)gcc
GDB = gdb-multiarch
EXE = main
SOURCES = $(wildcard *.c)
ASMSOURCES = $(wildcard *.s)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES)) $(patsubst %.s, %.o, $(ASMSOURCES))
DEPS = $(patsubst %.c, %.dep, $(SOURCES))

CFLAGS = -g -O1 -c
TARGET_ARCH = -mthumb -mcpu=cortex-m4
LDFLAGS = -T ld_ram.lds -nostartfiles
ASFLAGS = -g -c
TARGET_MACH = $(TARGET_ARCH)
LIBS = -lm

.PHONY: all debug gdbserver
all: $(EXE)
#	arm-none-eabi-gcc -c -g -O1 -mcpu=cortex-m4 -mthumb main.c -o main.o
#	arm-none-eabi-gcc -T ld_ram.lds main.o -o main.elf -nostartfiles

$(EXE): $(OBJECTS)
	echo $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@.elf $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@

%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

%.dep : %.c
	$(CC) -MM $< -MF $@

-include $(DEPS)

gdbserver:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) main.elf

clean:
	rm -f $(DEPS)
	rm -f $(OBJECTS)
	rm -f $(EXE).elf
