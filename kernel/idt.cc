// Copyright (c) 2019 FunSociety
#include <idt.h>
#include <gdt.h>

#define IDT_DESC_PRESENT 0x8
#define IDT_INTERRUPT_GATE_32 0xe
#define IDT_INTERRUPT_GATE_16 0x6
#define X86_RING_MAX 3

struct Idtr {
  heyos::uint32_t limit;
  heyos::uint16_t base;
} idtr;

// Declared in util.S
extern "C" void load_idt(); // lidt [idtr]
extern "C" void ignore_irq(); // iret


namespace heyos {

Idt::Idt(Gdt* gdt) {
  uint16_t kernel_code_segment = gdt->kernel_code_segment_selector();

  for (size_t i = 0; i < IDT_ENTRIES_COUNT; i++) {
    gates_[i] = GateDescriptor(&ignore_irq, kernel_code_segment, 0, IDT_INTERRUPT_GATE_32);
  }

  gates_[0x20] = GateDescriptor(&ignore_irq, kernel_code_segment, 0, IDT_INTERRUPT_GATE_32);
  gates_[0x21] = GateDescriptor(&ignore_irq, kernel_code_segment, 0, IDT_INTERRUPT_GATE_32);

  // Load IDT into CPU
  idtr.limit = IDT_ENTRIES_COUNT * sizeof(GateDescriptor) - 1;
  idtr.base = (uint32_t) this;
  load_idt();
}

void Idt::activate() const {
  __asm__ volatile("sti");
}

void Idt::deactivate() const {
  __asm__ volatile("cli");
}


Idt::GateDescriptor::GateDescriptor(void (*isr)(), uint16_t segment_selector,
                                    uint8_t privilege_level, uint8_t gate_type) {
  base_lo_ = ((uint32_t) isr) & 0xffff;
  base_hi_ = (((uint32_t) isr) >> 16) & 0xffff;
  segment_selector_ = segment_selector;
  reserved_ = 0;
  type_ = gate_type;
  flags_ = IDT_DESC_PRESENT | ((privilege_level & X86_RING_MAX) << 1);
}

}  // namespace heyos
