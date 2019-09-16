; util.S

; Segment selectors (currently hardcoded)
KERN_CODE_SEGMENT equ 0x10
KERN_DATA_SEGMENT equ 0x18


section .text
  global load_gdt
  extern gdtr;

; Loads GDT
; To complete the process of loading a new GDT, the segment registers
; need to be reloaded. The CS register must be loaded using a far jump.
load_gdt:
  lgdt [gdtr]
  jmp KERN_CODE_SEGMENT:_complete_flush
 
_complete_flush:
  mov ax, KERN_DATA_SEGMENT
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  ret
