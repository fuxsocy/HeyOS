// Copyright (c) 2019 FunSociety
#include <port.h>

namespace heyos {

void Port::wait() const {
  __asm__ volatile("jmp 1f;1:jmp 1f;1:");
}

void Port8Bit::write(uint8_t data) const {
  __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port_number_));
}

uint8_t Port8Bit::read() const {
  uint8_t data;
  __asm__ volatile("inb %1, %0" : "=a"(data) : "Nd"(port_number_));
  return data;
}

void Port8BitSlow::write(uint8_t data) const {
  Port8Bit::write(data);
  Port::wait();
}


void Port16Bit::write(uint16_t data) const {
  __asm__ volatile("outw %0, %1" : : "a"(data), "Nd"(port_number_));
}

uint16_t Port16Bit::read() const {
  uint16_t data;
  __asm__ volatile("inw %1, %0" : "=a"(data) : "Nd"(port_number_));
  return data;
}


void Port32Bit::write(uint32_t data) const {
  __asm__ volatile("outl %0, %1" : : "a"(data), "Nd"(port_number_));
}

uint32_t Port32Bit::read() const {
  uint32_t data;
  __asm__ volatile("inl %1, %0" : "=a"(data) : "Nd"(port_number_));
  return data;
}

}  // namespace heyos
