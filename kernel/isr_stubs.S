; interrupt.S

IRQ_BASE equ 0x20

; Exception/Interrupt handler generation macro
%macro DeclareExceptionHandler 1
[global handle_exception_%1]
handle_exception_%1:
  mov [interrupt_number], %1
  jmp _handle_interrupt
%endmacro

%macro DeclareIrqHandler 1
[global handle_irq_%1]
handle_irq_%1:
  mov [interrupt_number], byte (IRQ_BASE + %1)
  jmp _handle_interrupt
%endmacro



[section .bss]
  interrupt_number resb 1

[section .text]
[extern handle_irq]
  ; Generate IRQ handlers declarations with macro
  DeclareIrqHandler 0x00
  DeclareIrqHandler 0x01

_handle_interrupt:
  pusha                          ; Push all general purpose registers and segment registers
  push ds
  push es
  push fs
  push gs

  push esp                       ; Push second function parameter
  mov eax, [interrupt_number]
  push eax                       ; Push first function parameter
  call handle_irq                ; Call handle_irq(uint8_t irq_number, uint32_t esp)
  mov esp, eax                   ; Restore esp after executing the irq handler

  pop gs
  pop fs
  pop es
  pop ds
  popa

[global ignore_irq]
ignore_irq:
  iret
