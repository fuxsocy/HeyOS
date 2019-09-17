; util.S

; Segment selectors (currently hardcoded)
KERN_CODE_SEGMENT equ 0x10
KERN_DATA_SEGMENT equ 0x18


[section .text]

; Executes all global object ctors
[global exec_global_obj_ctors]
[extern start_ctor] ; linker.ld
[extern end_ctor] ; linker.ld

exec_global_obj_ctors:
  push ebx
  mov ebx, start_ctor
  jmp __have_next_ctor

__invoke_ctor:
  call [ebx]
  add ebx, 4

__have_next_ctor:
  cmp ebx, end_ctor
  jne __invoke_ctor
  pop ebx
  ret

  
; Loads GDT
; To complete the process of loading a new GDT, the segment registers
; need to be reloaded. The CS register must be loaded using a far jump.
[global load_gdt]
[extern gdtr]

load_gdt:
  lgdt [gdtr]
  jmp KERN_CODE_SEGMENT:__complete_flush
 
__complete_flush:
  mov ax, KERN_DATA_SEGMENT
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  ret


; Loads IDT
[global load_idt]
[extern idtr]

load_idt:
  lidt [idtr]
  ret
