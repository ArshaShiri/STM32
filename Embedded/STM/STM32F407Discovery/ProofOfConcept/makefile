CC=arm-none-eabi-gcc
MACHINE=cortex-m4
CFLAGS=-c -mcpu=$(MACHINE) -mthumb -std=gnu11 -Wall -O0

all:main.o led.o startup.o

# Target Dependency Recipe $^ is depencey $@ is the target
main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o:startup.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf