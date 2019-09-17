#ifndef __VGA_HPP
#define __VGA_HPP

#include <type.h>
#include <port.h>

#define VIDEO_MEMORY 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

namespace heyos {

template <typename T>
struct Pos {
    Pos() : x(0), y(0) {}
    Pos(T x, T y) : x(x), y(y) {}
    T x, y;
};


class Vga {
public:
    Vga();
    ~Vga();

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

    void Clear();
    void PutChar(char c);
    void Put(char* s);

    void CarriageReturn();
    void Newline();

    void set_cursor(uint8_t x, uint8_t y);
    void set_color(Vga::Color bg, Vga::Color fg);

private:
    static bool IsCharPrintable(uint8_t ascii);

    static uint16_t* video_memory_;

    Pos<uint8_t> cursor_;
    uint8_t color_; // bg << 4 | fg

    Port8Bit vga_command_port_;
    Port8Bit vga_data_port_;
};

}  // namespace heyos

#endif
