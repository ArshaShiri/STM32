CC=arm-none-eabi-gcc
MACHINE=cortex-m4
CFLAGS=-c -mcpu=$(MACHINE) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACHINE) -mthumb -mfloat-abi=soft --specs=nano.specs -T linkerScript.ld -Wl,-Map=final.map
LDFLAGSSEMIHOSTING= -mcpu=$(MACHINE) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T linkerScript.ld -Wl,-Map=final.map

all:main.o led.o startup.o syscalls.o final.elf

semi:main.o led.o startup.o syscalls.o finalsh.elf

# Target Dependency Recipe $^ is depencey $@ is the target
main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o:startup.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf:main.o led.o startup.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

finalsh.elf:main.o led.o startup.o
	$(CC) $(LDFLAGSSEMIHOSTING) -o $@ $^	

clean:
	rm -rf *.o *.elf *.map

load:
	openocd -f board/stm32f4discovery.cfg