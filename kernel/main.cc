// Copyright (c) 2019 FunSociety
#include <gdt.h>
#include <idt.h>

extern "C" void start_kernel(const void* multiboot_structure) {
  heyos::Gdt gdt;
  heyos::Idt idt(&gdt);
  idt.activate();
  while (1);
}
