
/* Memory map */
MEMORY {
  FLASH (r x) : ORIGIN = 0x08000000, LENGTH = 64K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Locations on Memory */
SECTIONS {
  .flash_top : {
    KEEP(*(.flash_top))
  } >FLASH

  .text : {
    . = ALIGN(4);
    *(.text)
    *(.text.*)
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* For other libs */
  .ARM.extab : {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

  .ARM.exidx : {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >FLASH

  _text_end = .;

  _data_copyaddress = .;

  .data : AT (_data_copyaddress) {
    . = ALIGN(4);
    _data_start = .;
    KEEP(*(.data))
    KEEP(*(.data.*))
    . = ALIGN(4);
    _data_end = .;
  } >RAM

  /* BSS AREA (Zero fill) */
  .bss : {
    . = ALIGN(4);
    _bss_start = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    _bss_end = .;
  } >RAM
}

