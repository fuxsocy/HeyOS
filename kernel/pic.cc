// Copyright (c) 2019 FunSociety
#include <pic.h>

#define IRQ_BASE 0x20
#define IRQ_COUNT 0x08

namespace heyos {

namespace pic {

Port8BitSlow pic_master_command(0x20);
Port8BitSlow pic_master_data(0x21);
Port8BitSlow pic_slave_command(0xa0);
Port8BitSlow pic_slave_data(0xa1);

void init() {
  // ICW1 (edge triggered mode, cascading controllers, expect ICW4)
  pic_master_command.write(0x11);
  pic_slave_command.write(0x11);

  // ICW2 (remapping the PICs to prevent hardware/software interrupts)
  // https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller#Remapping
  pic_master_data.write(IRQ_BASE);
  pic_slave_data.write(IRQ_BASE + IRQ_COUNT);

  // ICW3 (configure master/slave relationship)
  pic_master_data.write(0x04);
  pic_slave_data.write(0x02);

  // ICW4 (set x86 mode)
  pic_master_data.write(0x01);
  pic_slave_data.write(0x01);

  // Interrupt Mask -- start out with all IRQs enabled.
  pic_master_data.write(0x00);
  pic_slave_data.write(0x00);
}

}  // namespace pic

}  // namespace heyos
