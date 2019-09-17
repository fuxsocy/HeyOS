// Copyright (c) 2019 FunSociety
#include <gdt.h>

struct gdt_ptr {
  heyos::uint16_t size;
  heyos::uint32_t base;
} __attribute__((packed)) gdtr;

extern "C" void load_gdt(); // declared in util.S


namespace heyos {

gdt::gdt()
    : null_segment_descriptor_(0, 0, 0),
      unused_segment_descriptor_(0, 0, 0),
      kernel_code_segment_descriptor_(0, 64 * 1024 * 1024, 0x9a),
      kernel_data_segment_descriptor_(0, 64 * 1024 * 1024, 0x92) {
  gdtr.size = sizeof(gdt) - 1;
  gdtr.base = (uint32_t) this;
  load_gdt();
}

uint16_t gdt::kernel_code_segment_selector() const {
  return (uint32_t) &kernel_code_segment_descriptor_ - (uint32_t) this;
}

uint16_t gdt::kernel_data_segment_selector() const {
  return (uint32_t) &kernel_data_segment_descriptor_ - (uint32_t) this;
}


gdt::segment_descriptor::segment_descriptor(uint32_t base, uint32_t limit, uint8_t access) {
  // Check the limit to make sure that it can be encoded.
  if ((limit > 65536) && ((limit & 0xfff) != 0xfff)) {
    // FIXME: perform error handling here.
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
