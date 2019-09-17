// Copyright (c) 2019 FunSociety
#include <type.h>
#include <pic.h>

extern "C" heyos::uint32_t handle_irq(heyos::uint8_t irq_number, heyos::uint32_t esp) { 
  // Respond to hardware interrupts.
  if (irq_number >= 0x20 && irq_number < 0x30) {
    
    heyos::pic::pic_master_command.write(0x20);

    if (irq_number >= 0x28) {
      heyos::pic::pic_slave_command.write(0x20);
    }
  }

  return esp;
}
