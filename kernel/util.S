; util.S

section .text
  global load_gdt
  extern gdtr;

; Loads GDT
; To complete the process of loading a new GDT, the segment registers
; need to be reloaded. The CS register must be loaded using a far jump.
load_gdt:
  lgdt [gdtr]
  jmp 0x08:_complete_flush
 
_complete_flush:
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  ret
