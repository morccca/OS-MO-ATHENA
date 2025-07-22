#ifndef VIDEO_HPP
#define VIDEO_HPP

// Определяем типы вручную для bare metal
#include "types.h"

class Video 
{
public:
    static void initialize(); // инициализация
    static void clear(); // очистка экрана
    static void putchar(char c, uint8_t color = DEFAULT_COLOR); // вывод символа с цветом
    static void newline(); // новая строка
    static void print(const char* str, uint8_t color = DEFAULT_COLOR); // вывод строки с цветом
    static void println(const char* str); // вывод строки с переносом
    static void set_cursor(size_t x, size_t y); // курсор
    static uint8_t vga_color(uint8_t fg, uint8_t bg);
    static uint16_t vga_entry(char c, uint8_t color);

private:
    static constexpr uint8_t DEFAULT_COLOR = 0x07; // цвет текста

    // VGA буфер и состояние
    static uint16_t* const buffer;    // (0xB8000)
    static size_t cursor_x;
    static size_t cursor_y;
    static uint8_t current_color;

    static void check_bounds();

    
};

#endif 