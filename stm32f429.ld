ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);  /* Top of stack */

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
    KEEP(*(.init))
    KEEP(*(.fini))
  } > FLASH

  /* Initialized data: copied from flash to RAM */
  _sidata = LOADADDR(.data);
  .data : AT (_sidata)
  {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM

  /* Zero-initialized data */
  .bss :
  {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > RAM

  . = ALIGN(4);
  _end = .;
}
