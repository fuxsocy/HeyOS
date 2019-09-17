// Copyright (c) 2019 FunSociety
#include <idt.h>
#include <gdt.h>
#include <pic.h>

#define IDT_DESC_PRESENT 0x8
#define IDT_INTERRUPT_GATE_32 0xe
#define IDT_INTERRUPT_GATE_16 0x6
#define X86_RING_MAX 3

struct idt_ptr {
  heyos::uint16_t size;
  heyos::uint32_t base;
} __attribute__((packed)) idtr;

extern "C" {
void load_idt(); // util.S, lidt [idtr]
void ignore_irq(); // interrupt.S, iret
void handle_irq_0x00();
void handle_irq_0x01();
}


namespace heyos {

idt::idt(gdt* gdt) {
  uint16_t kernel_code_segment = gdt->kernel_code_segment_selector();

  for (size_t i = 0; i < IDT_ENTRIES_COUNT; i++) {
    gates_[i] = gate_descriptor(&ignore_irq, kernel_code_segment, 0, IDT_INTERRUPT_GATE_32);
  }

  gates_[0x20] = gate_descriptor(&handle_irq_0x00, kernel_code_segment, 0, IDT_INTERRUPT_GATE_32);
  gates_[0x21] = gate_descriptor(&handle_irq_0x01, kernel_code_segment, 0, IDT_INTERRUPT_GATE_32);

  pic::init();

  // Load IDT into CPU
  idtr.size = IDT_ENTRIES_COUNT * sizeof(gate_descriptor) - 1;
  idtr.base = (uint32_t) this;
  load_idt();
}

void idt::activate() const {
  __asm__ volatile("sti");
}

void idt::deactivate() const {
  __asm__ volatile("cli");
}


idt::gate_descriptor::gate_descriptor(void (*isr)(), uint16_t segment_selector,
                                    uint8_t privilege_level, uint8_t gate_type) {
  base_lo_ = ((uint32_t) isr) & 0xffff;
  base_hi_ = (((uint32_t) isr) >> 16) & 0xffff;
  segment_selector_ = segment_selector;
  reserved_ = 0;
  type_ = gate_type;
  flags_ = IDT_DESC_PRESENT | ((privilege_level & X86_RING_MAX) << 1);
}

}  // namespace heyos
