ENTRY(kernel_loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS{
  . = 0x00100000;

  .text : {
    *(.multiboot)
    *(.text)
  }

  .rodata ALIGN (0x1000) : {
    *(.rodata)
  }

  .data ALIGN (0x1000) : {
    start_ctor = .;
    KEEP(*( .init_array ));
    KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
    end_ctor = .;

    *(.data)
  }

  .bss : {
    *(COMMON)
    *(.bss)
  }
}
