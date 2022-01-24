CC=arm-none-eabi-gcc
MACHINE=cortex-m4
CFLAGS=-c -mcpu=$(MACHINE) -mthumb -std=gnu11 -Wall -O0
LDFLAGS=-nostdlib -T linkerScript.ld

all:main.o led.o startup.o final.elf

# Target Dependency Recipe $^ is depencey $@ is the target
main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o:startup.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf:main.o led.o startup.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf