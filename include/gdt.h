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

class Gdt {
 public: 
  Gdt();
  ~Gdt();

  uint16_t code_segment_selector() const;
  uint16_t data_segment_selector() const;

 private:
  class SegmentDescriptor {
   public:
    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
    ~SegmentDescriptor();
    uint32_t base() const;
    uint32_t limit() const;

   private:
    uint16_t limit_lo_;
    uint16_t base_lo_;
    uint8_t base_mid_;
    uint8_t access_;
    unsigned limit_hi_: 4;
    unsigned flags_: 4;
    uint8_t base_hi_;
  } __attribute__((packed));

  SegmentDescriptor null_segment_descriptor_;
  SegmentDescriptor unused_segment_descriptor_;
  SegmentDescriptor code_segment_descriptor_;
  SegmentDescriptor data_segment_descriptor_;
};

}  // namespace heyos

#endif // HEY_OS_GDT_H_
