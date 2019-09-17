// Copyright (c) 2019 FunSociety
#include <port.h>

namespace heyos {

void port::wait() const {
  __asm__ volatile("jmp 1f;1:jmp 1f;1:");
}

void port8::write(uint8_t data) const {
  __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port_number_));
}

uint8_t port8::read() const {
  uint8_t data;
  __asm__ volatile("inb %1, %0" : "=a"(data) : "Nd"(port_number_));
  return data;
}

void port8_slow::write(uint8_t data) const {
  port8::write(data);
  port::wait();
}


void port16::write(uint16_t data) const {
  __asm__ volatile("outw %0, %1" : : "a"(data), "Nd"(port_number_));
}

uint16_t port16::read() const {
  uint16_t data;
  __asm__ volatile("inw %1, %0" : "=a"(data) : "Nd"(port_number_));
  return data;
}


void port32::write(uint32_t data) const {
  __asm__ volatile("outl %0, %1" : : "a"(data), "Nd"(port_number_));
}

uint32_t port32::read() const {
  uint32_t data;
  __asm__ volatile("inl %1, %0" : "=a"(data) : "Nd"(port_number_));
  return data;
}

}  // namespace heyos
