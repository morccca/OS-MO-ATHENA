#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <cstdint> 

class Video 
{
public:

    static void initialize();

    static void clear(); // очистка

    static void putchar(char c, uint8_t color = DEFAULT_COLOR); // вывод символа с цветом

    static void print(const char* str, uint8_t color = DEFAULT_COLOR); // вывод строки с цевтом

    static void set_cursor(size_t x, size_t y); // курсор

    
    static constexpr uint8_t DEFAULT_COLOR = 0x07; // цвет текста
    static uint8_t vga_color(uint8_t fg, uint8_t bg);

private:
    static uint16_t* const buffer;    // (0xB8000)
    static size_t cursor_x;           
    static size_t cursor_y;           
    static uint8_t current_color;     
    
    static uint16_t vga_entry(char c, uint8_t color);
    
    static void check_bounds(); // ПРОВЕРКА
};

#endif 