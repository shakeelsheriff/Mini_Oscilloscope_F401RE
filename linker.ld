/* This is the The entry directive (ENTRY) specifying the entry point of the program */
ENTRY(Reset_Handler)

/* This is the Memory directive (MEMORY) Defining Limit of the Memory */
MEMORY{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

/*Symbol to hold Stack Pointer*/
_estack = ORIGIN(SRAM) + LENGTH(SRAM); /* top of RAM */

/*Delaring heap and Stack Sizes*/
_max_heap_size = 0x200;
_max_stack_size = 0x400;


/* This is the sections directive (SECTIONS) defines the mapping and ordering of sections from input files into the output file */
SECTIONS{
    .text :
    {
        . = ALIGN(4);
        *(.isr_vector_tbl)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    }>FLASH
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT> FLASH
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        _ebss = .;
    }> SRAM
}