/* vga.cpp
 *
 * Virtual Terminal driver. Each VT character is represented by every 16 bits
 * starting from the video memory address 0xb8000. An illustration would help:
 *
 * high            low
 *  ....|....|........ (16 bit)
 *   bg | fg | ASCII
 */

#include <vga.h>

namespace heyos {

uint16_t* Vga::video_memory_ = (uint16_t*) VIDEO_MEMORY;

Vga::Vga()
    : cursor_(0, 0),
      color_(Vga::BLACK << 4 | Vga::LIGHT_GREY),
      vga_command_port_(0x3d4),
      vga_data_port_(0x3d5) {}

Vga::~Vga() {}


void Vga::Clear() {
    for (int i = 0; i < 80 * 25; i++) {
        video_memory_[i] = (video_memory_[i] & 0xff00) | 0x0000;
    }
    set_cursor(0, 0);
}

void Vga::PutChar(char c) {
    if (c == '\n') {
        Newline();
        return;
    }

    if (!Vga::IsCharPrintable(c)) {
        return;
    }

    uint32_t cur = cursor_.y * VGA_WIDTH + cursor_.x;
    video_memory_[cur] = color_ << 8 | c;

    set_cursor(++cursor_.x, cursor_.y);
    if (cursor_.x >= VGA_WIDTH) {
        Newline();
    }
}

static uint32_t strlen(char* s) {
  uint32_t len = 0;
  while (*s++) {
    len++;
  }
  return len;
}


void Vga::Put(char* s) {
    for (uint32_t i = 0; i < strlen(s); i++) {
        PutChar(s[i]);
    }
}

void Vga::CarriageReturn() {
    cursor_.x = 0;
    set_cursor(cursor_.x, cursor_.y);
}

void Vga::Newline() {
    cursor_.x = 0;
    set_cursor(cursor_.x, ++cursor_.y);
}


void Vga::set_cursor(uint8_t x, uint8_t y) {
    uint16_t pos = y * VGA_WIDTH + x;
    vga_command_port_.write(0x0f);
    vga_data_port_.write((uint8_t) (pos & 0xff));
    vga_command_port_.write(0x0e);
    vga_data_port_.write((uint8_t) (pos >> 8) & 0xff);
}

void Vga::set_color(Vga::Color bg, Vga::Color fg) {
    color_ = bg << 4 | fg;
}


bool Vga::IsCharPrintable(uint8_t ascii) {
    return ascii >= 0x20 && ascii <= 0x7e;
}

}  // namespace heyos
