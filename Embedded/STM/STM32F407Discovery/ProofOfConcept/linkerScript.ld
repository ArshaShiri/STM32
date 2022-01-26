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
    *(.isr_vector)
    *(.text) /* Merge the text section of all input files */
    *(.rodata)
    . = ALIGN(4);
    end_of_text = .; /* Store the updated location counter value in the symbol 'end_of_text'  Location counter, always tracks VMA not LMA*/
  }> FLASH  /* Virtual meomory address(VMA) and load memory address(LMA) are the same for this section */

  .data :
  {
    start_of_data = .; /* Assign a value to the symbol 'start_of_data'  The value equals to VMA which is SRAM*/
    *(.data)
    . = ALIGN(4);
    end_of_data = .;
  }> SRAM AT> FLASH

  .bss :
  {
    start_of_bss = .;
    *(.bss)
    *(.COMMON)
    . = ALIGN(4);
    end_of_bss = .;
  }> SRAM
}