PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)gcc

CFLAGS = -g -Og
TARGET_ARCH = -mthumb -mcpu=cortex-m4
LDFLAGS = -g
ASFLAGS = -g
TARGET_MACH = $(TARGET_ARCH)

LIBS = -lm

NAME = main.elf
OFILES = t1.o t2.o main.o stubs.o
DEPS = $(patsubst %.o, %.dep, $(OFILES))

vpath %.c libs

.PHONY: all clean

all: $(NAME)

$(NAME): $(OFILES)
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

# %.o : %.c
# 	$(GCC) $(CFLAGS) $< -o $@

%.dep : %.c
	$(CC) -MM $< -MF $@

-include $(DEPS)

clean:
	rm -f $(DEPS)
	rm -f $(OFILES)
	rm -f $(NAME)
