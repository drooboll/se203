PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
GDB   = gdb-multiarch
ASFLAGS = -g
LDFLAGS = -g -Ttext 0x20000000

ASFILES  = $(wildcard *.s)
ELFFILES = $(patsubst %.s,%.elf,$(ASFILES))

all: $(ELFFILES)

%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

%.elf:%.o
	$(LD) $(LDFLAGS) $< -o $@

.PHONY: connect debug clean

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB)

clean:
	rm -f $(ELFFILES)
