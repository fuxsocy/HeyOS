#ifndef __VGA_HPP
#define __VGA_HPP

#include <type.h>
#include <port.h>

#define VIDEO_MEMORY 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

namespace heyos {

template <typename T>
struct pos {
  pos() : x(), y() {}
  pos(T x, T y) : x(x), y(y) {}
  T x, y;
};


class vga {
 public:
  vga();
  ~vga() = default;

  enum Color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE
  };

  void clear();
  void putc(char c);
  void puts(char* s);

  void cr();
  void lf();

  void set_cursor(uint8_t x, uint8_t y);
  void set_color(vga::Color bg, vga::Color fg);

 private:
  static bool is_printable(uint8_t ascii);

  static uint16_t* video_memory_;

  pos<uint8_t> cursor_;
  uint8_t color_; // bg << 4 | fg

  port8 vga_command_port_;
  port8 vga_data_port_;
};

}  // namespace heyos

#endif
