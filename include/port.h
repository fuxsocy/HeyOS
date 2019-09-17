// Copyright (c) 2019 FunSociety
#ifndef HEY_OS_PORT_H_
#define HEY_OS_PORT_H_

#include <type.h>

namespace heyos {

class port {
 protected:
  port(uint16_t port_number) : port_number_(port_number) {}
  ~port() = default;

  virtual void wait() const;
  uint16_t port_number_;
};


class port8 : public port {
 public:
  port8(uint16_t port_number) : port(port_number) {}
  ~port8() = default;

  virtual void write(uint8_t data) const;
  virtual uint8_t read() const;
};


class port8_slow : public port8 {
 public:
  port8_slow(uint16_t port_number) : port8(port_number) {}
  ~port8_slow() = default;

  virtual void write(uint8_t data) const override;
};


class port16 : public port {
 public:
  port16(uint16_t port_number) : port(port_number) {}
  ~port16() = default;

  virtual void write(uint16_t data) const;
  virtual uint16_t read() const;
};


class port32 : public port {
 public:
  port32(uint16_t port_number) : port(port_number) {}
  ~port32() = default;

  virtual void write(uint32_t data) const;
  virtual uint32_t read() const;
};

}  // namespace heyos

#endif // HEY_OS_PORT_H_
