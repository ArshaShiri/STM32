/* Define the entry point here. It is also used by the debugger */
ENTRY(Reset_Handler)

MEMORY
{
  FLASH(rx):ORIGIN = 0x08000000, LENGTH = 1024K
  SRAM(rwx):ORIGIN = 0x20000000, LENGTH = 128K /* Both SRAM1 and SRAM2 */
}/* A symbol declartaion. Not a variable !!! */

SECTIONS
{
  .text :
  {
    start_of_constructors = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array*))
    end_of_constructors = .;
    *(.isr_vector)
    *(.text) /* Merge the text section of all input files */
    *(.text.*) /* Merge the text section the std lib that have names like text.something. See the effect of this by runnuin arm-none-eabi-objdump -h final.elf with and without this section.*/
    *(.init)
    *(.fini)
    *(.rodata)
    *(.rodata.*)
    . = ALIGN(4);
    end_of_text = .; /* Store the updated location counter value in the symbol 'end_of_text'  Location counter, always tracks VMA not LMA*/
  }> FLASH  /* Virtual meomory address(VMA) and load memory address(LMA) are the same for this section */

  load_address_of_data = LOADADDR(.data);
  .data :
  {
    start_of_data = .; /* Assign a value to the symbol 'start_of_data'  The value equals to VMA which is SRAM*/
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    end_of_data = .;
  }> SRAM AT> FLASH

  .bss :
  {
    start_of_bss = .;
    __bss_start__ = start_of_bss;
    *(.bss)
    *(.bss.*)
    *(.COMMON)
    . = ALIGN(4);
    end_of_bss = .;
    __bss_end__ = end_of_bss;
    . = ALIGN(4);
    end = .; /* The end symbol tracks the heap. The heap starts after bss section. */
    __end__ = .; /* The same symbol as above but for semi hosting. */
  }> SRAM
}
