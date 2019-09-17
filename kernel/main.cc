// Copyright (c) 2019 FunSociety
#include <gdt.h>
#include <idt.h>

extern "C" void start_kernel(const void* multiboot_structure) {
  heyos::gdt gdt;
  heyos::idt idt(&gdt);
  idt.activate();
  while (1);
}
