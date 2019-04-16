
MEMORY
{
    rom : ORIGIN = 0x0000C000, LENGTH = 0x1000
    ram : ORIGIN = 0x10010000, LENGTH = 0x1000
}

SECTIONS
{
    .text : { *(.text*) } > rom
    .rodata : { *(.rodata*) } > rom
    .bss : { *(.bss*) } > ram
}

