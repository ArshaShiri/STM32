CC=arm-none-eabi-gcc
MACHINE=cortex-m4
CFLAGS=-c -mcpu=$(MACHINE) -mthumb -std=gnu11 -O0

# Target Dependency Recipe $^ is depencey $@ is the target
main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^