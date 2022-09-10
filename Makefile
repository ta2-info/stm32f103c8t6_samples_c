
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

all: blink.bin blinkwithtimer.bin usart1_tx.bin usart1_rx.bin usart1_rxtx.bin usart1withdma_rx.bin usart2_tx_10digits.bin

blink.bin: blink.elf
	$(OBJCOPY) -O binary $< $@

blinkwithtimer.bin: blinkwithtimer.elf
	$(OBJCOPY) -O binary $< $@

usart1_tx.bin: usart1_tx.elf
	$(OBJCOPY) -O binary $< $@

usart1_rx.bin: usart1_rx.elf
	$(OBJCOPY) -O binary $< $@

usart1_rxtx.bin: usart1_rxtx.elf
	$(OBJCOPY) -O binary $< $@

usart1withdma_rx.bin: usart1withdma_rx.elf
	$(OBJCOPY) -O binary $< $@

usart2_tx_10digits.bin: usart2_tx_10digits.elf
	$(OBJCOPY) -O binary $< $@


blink.elf: vector.o blink.o
	$(LD) $(LDOPT) -o $@ vector.o blink.o -Map blink.map

blinkwithtimer.elf: vector.o interrupt.o blinkwithtimer.o
	$(LD) $(LDOPT) -o $@ vector.o interrupt.o blinkwithtimer.o -Map blinkwithtimer.map

usart1_tx.elf: vector.o usart1_tx.o
	$(LD) $(LDOPT) -o $@ vector.o usart1_tx.o -Map usart1_tx.map

usart1_rx.elf: vector.o usart1_rx.o
	$(LD) $(LDOPT) -o $@ vector.o usart1_rx.o -Map usart1_rx.map

usart1_rxtx.elf: vector.o usart1_rxtx.o
	$(LD) $(LDOPT) -o $@ vector.o usart1_rxtx.o -Map usart1_rxtx.map

usart1withdma_rx.elf: vector.o usart1withdma_rx.o
	$(LD) $(LDOPT) -o $@ vector.o interrupt.o usart1withdma_rx.o -Map usart1withdma_rx.map

usart2_tx_10digits.elf: vector.o usart2_tx_10digits.o
	$(LD) $(LDOPT) -o $@ vector.o usart2_tx_10digits.o -Map usart2_tx_10digits.map


vector.o: vector.s
	$(ASM) $(ASMOPT) -o $@ $<

interrupt.o: interrupt.c
	$(CC) $(CCOPT) -o $@ $<

blink.o: blink.c
	$(CC) $(CCOPT) -o $@ $<

blinkwithtimer.o: blinkwithtimer.c
	$(CC) $(CCOPT) -o $@ $<

usart1_tx.o: usart1_tx.c
	$(CC) $(CCOPT) -o $@ $<

usart1_rx.o: usart1_rx.c
	$(CC) $(CCOPT) -o $@ $<

usart1_rxtx.o: usart1_rxtx.c
	$(CC) $(CCOPT) -o $@ $<

usart1withdma_rx.o: usart1withdma_rx.c
	$(CC) $(CCOPT) -o $@ $<

usart2_tx_10digits.o: usart2_tx_10digits.c
	$(CC) $(CCOPT) -o $@ $<


install-blink:
#	$(ST-FLASH) write blink.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./blink.bin $(BASE_FLASH) verify reset exit"

install-blinkwithtimer:
#	$(ST-FLASH) write blinkwithtimer.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./blinkwithtimer.bin $(BASE_FLASH) verify reset exit"

install-usart1_tx:
#	$(ST-FLASH) write usart1_tx.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./usart1_tx.bin $(BASE_FLASH) verify reset exit"

install-usart1_rx:
#	$(ST-FLASH) write usart1_rx.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./usart1_rx.bin $(BASE_FLASH) verify reset exit"

install-usart1_rxtx:
#	$(ST-FLASH) write usart1_rxtx.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./usart1_rxtx.bin $(BASE_FLASH) verify reset exit"

install-usart1withdma_rx:
#	$(ST-FLASH) write usart1withdma_rx.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./usart1withdma_rx.bin $(BASE_FLASH) verify reset exit"

install-usart2_tx_10digits:
#	$(ST-FLASH) write usart2_tx_10digits.bin $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./usart2_tx_10digits.bin $(BASE_FLASH) verify reset exit"


dis-blink:
	$(OBJDUMP) -D blink.elf

dis-blinkwithtimer:
	$(OBJDUMP) -D blinkwithtimer.elf

dis-usart1_tx:
	$(OBJDUMP) -D usart1_tx.elf

dis-usart1_rx:
	$(OBJDUMP) -D usart1_rx.elf

dis-usart1_rxtx:
	$(OBJDUMP) -D usart1_rxtx.elf

dis-usart1withdma_rx:
	$(OBJDUMP) -D usart1withdma_rx.elf

dis-usart2_tx_10digits:
	$(OBJDUMP) -D usart2_tx_10digits.elf


debugserver:
#	$(ST-UTIL) -p 3333 -m
	$(OPENOCD) -d1 -f interface/stlink.cfg -f target/stm32f1x.cfg


debug-blink:
	$(GDB) -x debug.gdb blink.elf
#	$(LLDB) -s debug.lldb blink.elf

debug-blinkwithtimer:
	$(GDB) -x debug.gdb blinkwithtimer.elf
#	$(LLDB) -s debug.lldb blinkwithtimer.elf

debug-usart1_tx:
	$(GDB) -x debug.gdb usart1_tx.elf
#	$(LLDB) -s debug.lldb usart1_tx.elf

debug-usart1_rx:
	$(GDB) -x debug.gdb usart1_rx.elf
#	$(LLDB) -s debug.lldb usart1_rx.elf

debug-usart1_rxtx:
	$(GDB) -x debug.gdb usart1_rxtx.elf
#	$(LLDB) -s debug.lldb usart1_rxtx.elf

debug-usart1withdma_rx:
	$(GDB) -x debug.gdb usart1withdma_rx.elf
#	$(LLDB) -s debug.lldb usart1withdma_rx.elf

debug-usart2_tx_10digits:
	$(GDB) -x debug.gdb usart2_tx_10digits.elf
#	$(LLDB) -s debug.lldb usart2_tx_10digits.elf


clean:
	$(RM) *.bin
	$(RM) *.elf
	$(RM) *.o
	$(RM) *.map

