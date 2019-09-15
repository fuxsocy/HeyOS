// Copyright (c) 2019 FunSociety
#ifndef HEY_OS_PORT_H_
#define HEY_OS_PORT_H_

#include <type.h>

namespace heyos {

class Port {
 protected:
  Port(uint16_t port_number) : port_number_(port_number) {}
  ~Port() = default;

  virtual void wait() const;
  uint16_t port_number_;
};


class Port8Bit : public Port {
 public:
  Port8Bit(uint16_t port_number) : Port(port_number) {}
  ~Port8Bit() = default;

  virtual void write(uint8_t data) const;
  virtual uint8_t read() const;
};


class Port8BitSlow : public Port8Bit {
 public:
  Port8BitSlow(uint16_t port_number) : Port8Bit(port_number) {}
  ~Port8BitSlow() = default;

  virtual void write(uint8_t data) const override;
};


class Port16Bit : public Port {
 public:
  Port16Bit(uint16_t port_number) : Port(port_number) {}
  ~Port16Bit() = default;

  virtual void write(uint16_t data) const;
  virtual uint16_t read() const;
};


class Port32Bit : public Port {
 public:
  Port32Bit(uint16_t port_number) : Port(port_number) {}
  ~Port32Bit() = default;

  virtual void write(uint32_t data) const;
  virtual uint32_t read() const;
};

}  // namespace heyos

#endif // HEY_OS_PORT_H_
