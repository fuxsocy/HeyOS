// Copyright (c) 2019 FunSociety
//
// GDT (Global Descriptor Table) is specific to IA-32 architecture.
// It contains entries telling the CPU about memory segments.
// A similar Interrupts Descriptor Table exists containing tasks and
// interrupts descriptors.
//
// Low                                                                 High
//
//    0        1        2        3        4        5         6        7
// ........|........|........|........|........|........|....|....|........
//       limit      |           base           | access |limt|flag|  base
// -----------------+--------------------------+--------+---------+--------
//   0-7   |  8-15  |   0-7  |  8-15  |  16-23 |        |16-19    |  24-31
//
// Reference:
// https://wiki.osdev.org/Global_Descriptor_Table
//
#ifndef HEY_OS_GDT_H_
#define HEY_OS_GDT_H_

#include <type.h>

namespace heyos {

class gdt {
 public: 
  gdt();
  ~gdt() = default;

  // A segment selector is an offset to GDT.
  // The size of GDT is 65536 (2^16) bytes in total.
  uint16_t kernel_code_segment_selector() const;
  uint16_t kernel_data_segment_selector() const;

 private:
  class segment_descriptor {
   public:
    segment_descriptor(uint32_t base, uint32_t limit, uint8_t access);
    ~segment_descriptor() = default;

   private:
    uint16_t limit_lo_;
    uint16_t base_lo_;
    uint8_t base_mid_;
    uint8_t access_;
    unsigned limit_hi_: 4;
    unsigned flags_: 4;
    uint8_t base_hi_;
  } __attribute__((packed));

  segment_descriptor null_segment_descriptor_;
  segment_descriptor unused_segment_descriptor_;
  segment_descriptor kernel_code_segment_descriptor_;
  segment_descriptor kernel_data_segment_descriptor_;
};

}  // namespace heyos

#endif // HEY_OS_GDT_H_
