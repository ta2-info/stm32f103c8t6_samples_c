
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

%.o:%.s
	$(ASM) $(ASMOPT) -o $@ $<

%.o:%.c
	$(CC) $(CCOPT) -o $@ $<

%.bin:%.elf
	$(OBJCOPY) -O binary $< $@

all: blink.bin blinkwithtimer.bin usart1_tx.bin usart1_rx.bin usart1_rxtx.bin usart1withdma_rx.bin usart2_tx_10digits.bin

blink.elf: vector.o blink.o
	$(LD) $(LDOPT) -o $@ $^ -Map $(@:.elf=.map)

blinkwithtimer.elf: vector.o interrupt.o blinkwithtimer.o
	$(LD) $(LDOPT) -o $@ $^ -Map $(@:.elf=.map)

usart1_tx.elf: vector.o usart1_tx.o
	$(LD) $(LDOPT) -o $@ $^ -Map $(@:.elf=.map)

usart1_rx.elf: vector.o usart1_rx.o
	$(LD) $(LDOPT) -o $@ $^ -Map $(@:.elf=.map)

usart1_rxtx.elf: vector.o usart1_rxtx.o
	$(LD) $(LDOPT) -o $@ $^ -Map $(@:.elf=.map)

usart1withdma_rx.elf: vector.o interrupt.o usart1withdma_rx.o
	$(LD) $(LDOPT) -o $@ $^ -Map $(@:.elf=.map)

usart2_tx_10digits.elf: vector.o usart2_tx_10digits.o
	$(LD) $(LDOPT) -o $@ $^ -Map $(@:.elf=.map)


install-blink:
#	$(ST-FLASH) write $(@:install-%=%.bin) $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./$(@:install-%=%.bin) $(BASE_FLASH) verify reset exit"

install-blinkwithtimer:
#	$(ST-FLASH) write $(@:install-%=%.bin) $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./$(@:install-%=%.bin) $(BASE_FLASH) verify reset exit"

install-usart1_tx:
#	$(ST-FLASH) write $(@:install-%=%.bin) $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./$(@:install-%=%.bin) $(BASE_FLASH) verify reset exit"

install-usart1_rx:
#	$(ST-FLASH) write $(@:install-%=%.bin) $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./$(@:install-%=%.bin) $(BASE_FLASH) verify reset exit"

install-usart1_rxtx:
#	$(ST-FLASH) write $(@:install-%=%.bin) $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./$(@:install-%=%.bin) $(BASE_FLASH) verify reset exit"

install-usart1withdma_rx:
#	$(ST-FLASH) write $(@:install-%=%.bin) $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./$(@:install-%=%.bin) $(BASE_FLASH) verify reset exit"

install-usart2_tx_10digits:
#	$(ST-FLASH) write $(@:install-%=%.bin) $(BASE_FLASH)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg  -c "program ./$(@:install-%=%.bin) $(BASE_FLASH) verify reset exit"


dis-blink:
	$(OBJDUMP) -D $(@:dis-%=%.elf)

dis-blinkwithtimer:
	$(OBJDUMP) -D $(@:dis-%=%.elf)

dis-usart1_tx:
	$(OBJDUMP) -D $(@:dis-%=%.elf)

dis-usart1_rx:
	$(OBJDUMP) -D $(@:dis-%=%.elf)

dis-usart1_rxtx:
	$(OBJDUMP) -D $(@:dis-%=%.elf)

dis-usart1withdma_rx:
	$(OBJDUMP) -D $(@:dis-%=%.elf)

dis-usart2_tx_10digits:
	$(OBJDUMP) -D $(@:dis-%=%.elf)


debugserver:
#	$(ST-UTIL) -p 3333 -m
	$(OPENOCD) -d1 -f interface/stlink.cfg -f target/stm32f1x.cfg


debug-blink:
	$(GDB) -x debug.gdb $(@:debug-%=%.elf)
#	$(LLDB) -s debug.lldb $(@:debug-%=%.elf)

debug-blinkwithtimer:
	$(GDB) -x debug.gdb $(@:debug-%=%.elf)
#	$(LLDB) -s debug.lldb $(@:debug-%=%.elf)

debug-usart1_tx:
	$(GDB) -x debug.gdb $(@:debug-%=%.elf)
#	$(LLDB) -s debug.lldb $(@:debug-%=%.elf)

debug-usart1_rx:
	$(GDB) -x debug.gdb $(@:debug-%=%.elf)
#	$(LLDB) -s debug.lldb $(@:debug-%=%.elf)

debug-usart1_rxtx:
	$(GDB) -x debug.gdb $(@:debug-%=%.elf)
#	$(LLDB) -s debug.lldb $(@:debug-%=%.elf)

debug-usart1withdma_rx:
	$(GDB) -x debug.gdb $(@:debug-%=%.elf)
#	$(LLDB) -s debug.lldb $(@:debug-%=%.elf)

debug-usart2_tx_10digits:
	$(GDB) -x debug.gdb $(@:debug-%=%.elf)
#	$(LLDB) -s debug.lldb $(@:debug-%=%.elf)


clean:
	$(RM) *.bin
	$(RM) *.elf
	$(RM) *.o
	$(RM) *.map

