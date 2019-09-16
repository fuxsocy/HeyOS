; loader.S - kernel loader
;
; We'll use assembly to set up the .multiboot section, and before executing start_kernel()
; in main.cpp, we have to make sure that it has a stack to use. To do that, I manually
; reserve 2 MiB of stack with `resb` (see .bss), and then `mov esp, stack_top`.
MAGIC equ 0x1badb002                 ; Magic number which marks this binary as a kernel
FLAGS equ 0x0                        ; Multiboot flag
CHECKSUM equ -(MAGIC+FLAGS)          ; MAGIC + CHECKSUM + FLAGS should be 0
STACK_SIZE equ 2 * 1024 * 1024       ; Kernel stack size


; Kernel Multiboot Header
; Note: The `align n` directive ensures that the next byte to be assembled will be 
; placed at a byte location of multiple of n.
[section .multiboot]                 ; The multiboot standard requires this header to be
  align 4                            ; set within the first 8KiB, and be 4-byte aligned
  dd MAGIC                           ; 4-byte magic number
  dd FLAGS                           ; 4-byte flags
  dd CHECKSUM                        ; 4-byte checksum


; Kernel Stack
; According to System V ABI standards (https://wiki.osdev.org/System_V_ABI), the stack
; on a i386 system must be 16-byte aligned just before the call instruction is called.
; Stack grows downards (towards low mem addr) on x86 systems
[section .bss]                       ; It is up to the kernel to provide a call stack.
  align 16

stack_bottom:
  resb STACK_SIZE

stack_top:


[section .text]

[extern start_kernel]
[global kernel_loader]

kernel_loader:
  mov esp, stack_top               ; Point esp to the top of the stack
  push ebx                         ; start_kernel()'s first param: multiboot structure
  call start_kernel                ; Continue executing our kernel in main.cpp

end_kernel:
  cli                              ; Disable interrupts
  hlt                              ; Wait for the next interrupt
  jmp end_kernel                   ; Jump to end_kernel again, just in case a interrupt occurs
