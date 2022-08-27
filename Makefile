
## Memory info of STM32F103C8T6
#
# ** Flash **
#  64kB
#  0x08000000 - 0x0800ffff
#
# ** SRAM **
#  20kB
#  0x20000000 - 0x20004fff

# base address of flash
BASE_FLASH := 0x08000000

CC := arm-none-eabi-gcc
ASM := arm-none-eabi-as
LD := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy
OBJDUMP := arm-none-eabi-objdump
GDB := arm-none-eabi-gdb
LLDB := lldb
ST-FLASH := st-flash
ST-UTIL := st-util
OPENOCD := openocd

CCOPT = -c -g -mcpu=cortex-m3 -mthumb
ASMOPT = -g -mcpu=cortex-m3 -mthumb
LDOPT = -Tstm32f103c8.ld

all: blink.bin

blink.bin: blink.elf
	$(OBJCOPY) -O binary $< $@

blink.elf: vector.o main.o
	$(LD) $(LDOPT) -o $@ vector.o main.o -Map main.map

vector.o: vector.s
	$(ASM) $(ASMOPT) -o $@ $<

main.o: main.c
	$(CC) $(CCOPT) -o $@ $<

install:
#	$(ST-FLASH) write blink.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./blink.bin $(BASE_FLASH) verify reset exit"

debugserver:
#	$(ST-UTIL) -p 3333 -m
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg

debug:
	$(GDB) -x debug.gdb blink.elf
#	$(LLDB) -s debug.lldb blink.elf

clean:
	$(RM) blink.bin
	$(RM) blink.elf
	$(RM) vector.o
	$(RM) main.o
	$(RM) main.map

dis:
	$(OBJDUMP) -D blink.elf

