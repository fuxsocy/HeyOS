// Copyright (c) 2019 FunSociety
//
// IDT (Interrupt Descriptor Table) is specific to the IA-32 architecture.
// It is the Protected mode counterpart to the Real Mode IVT (Interrupt Vector Table)
// telling where the ISR (Interrupt Service Routines) are located.
// It is similar to the GDT (Global Descriptor Table) in structure.
//
// The IDT entries are called "gates" or "gate descriptors".
// It can contain: Interrupt Gates, Task Gates and Trap Gates.
//
// Before implementing the IDT, make sure we have a working GDT.
//
// Reference:
// https://wiki.osdev.org/Interrupt_Descriptor_Table
//
#ifndef HEY_OS_IDT_H_
#define HEY_OS_IDT_H_

#include <type.h>

#define IDT_ENTRIES_COUNT 256

namespace heyos {

// Forward declaration of Gdt
class Gdt;

class Idt {
 public:
  Idt(Gdt* gdt);
  ~Idt() = default;

  void activate() const;
  void deactivate() const;

 private:
  class GateDescriptor {
   public:
    GateDescriptor() = default;
    GateDescriptor(void (*isr)(), uint16_t segment_selector,
                   uint8_t privilege_level, uint8_t gate_type);
    ~GateDescriptor() = default;

   private:
    uint16_t base_lo_;
    uint16_t segment_selector_;
    uint8_t reserved_;
    unsigned type_: 4;
    unsigned flags_: 4;
    uint16_t base_hi_;
  } __attribute__((packed));

  GateDescriptor gates_[IDT_ENTRIES_COUNT];
};

}  // namespace heyos

#endif // HEY_OS_IDT_H_
