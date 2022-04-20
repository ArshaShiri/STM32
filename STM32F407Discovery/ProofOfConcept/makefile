CC=arm-none-eabi-gcc
MACHINE=cortex-m4
#DEBUG = 1
CFLAGS=-c -mcpu=$(MACHINE) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O3
# ifeq ($(DEBUG), 1)
# CFLAGS += -g3 -gdwarf-2 # original: -g
# endif
LDFLAGS= -mcpu=$(MACHINE) -mthumb -mfloat-abi=soft --specs=nano.specs -T linkerScript.ld -Wl,-Map=final.map
LDFLAGSSEMIHOSTING= -mcpu=$(MACHINE) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T linkerScript.ld -Wl,-Map=final.map

all:main.o startup.o syscalls.o final.elf artifacts

semi:main.o startup.o syscalls.o finalsh.elf

# Target Dependency Recipe $^ is depencey $@ is the target
main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o:startup.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf:main.o startup.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^

finalsh.elf:main.o startup.o
	$(CC) $(LDFLAGSSEMIHOSTING) -o $@ $^	

clean:
	rm -rf *.o *.elf *.bin

load:
	openocd -f board/stm32f4discovery.cfg

loadbin:
	st-flash --reset write final.bin 0x08000000

artifacts:
	arm-none-eabi-objcopy -O binary final.elf final.bin
	arm-none-eabi-objdump -h *.elf > objdump.headers
	arm-none-eabi-objdump -D *.elf > objdump.disassemble
	arm-none-eabi-objdump -d *.elf > objdump.disassembleExe
