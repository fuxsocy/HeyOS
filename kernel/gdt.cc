// Copyright (c) 2019 FunSociety
#include <gdt.h>

struct Gdtr {
  heyos::uint32_t base;
  heyos::uint16_t limit;
} gdtr;

extern "C" void load_gdt(); // declared in util.S


namespace heyos {

Gdt::Gdt()
    : null_segment_descriptor_(0, 0, 0),
      unused_segment_descriptor_(0, 0, 0),
      kernel_code_segment_descriptor_(0, 0xfffff, 0x9a),
      kernel_data_segment_descriptor_(0, 0xfffff, 0x92) {
  gdtr.base = (uint32_t) this;
  gdtr.limit = sizeof(Gdt) - 1;
  load_gdt();
}

uint16_t Gdt::kernel_code_segment_selector() const {
  return (uint32_t) &kernel_code_segment_descriptor_ - (uint32_t) this;
}

uint16_t Gdt::kernel_data_segment_selector() const {
  return (uint32_t) &kernel_data_segment_descriptor_ - (uint32_t) this;
}


Gdt::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t access) {
  // Check the limit to make sure that it can be encoded.
  if ((limit > 65536) && ((limit & 0xfff) != 0xfff)) {
    // FIXME: perform error handling here.
    return;
  }

  if (limit <= 65536) {
    flags_ = 0x4;
  } else {
    // Adjust granularity if required
    limit >>= 12;
    flags_ = 0xc;
  }

  limit_lo_ = limit & 0xffff;
  limit_hi_ = (limit >> 16) & 0xf;

  base_lo_ = base & 0xffff;
  base_mid_ = (base >> 16) & 0xff;
  base_hi_ = (base >> 24) & 0xff;

  access_ = access;
}

}  // namespace heyos
