#include "../include/video.h"

#define WIDTH 80
#define HEIGHT 25

uint16_t* const Video::buffer = reinterpret_cast<uint16_t*>(0xB8000);

size_t Video::cursor_x = 0;
size_t Video::cursor_y = 0;

uint8_t Video::current_color = Video::DEFAULT_COLOR;

void Video::initialize() 
{
    clear();
}

void Video::clear() 
{
    for (size_t y = 0; y < HEIGHT; y++) 
    {
        for (size_t x = 0; x < WIDTH; x++) 
        {
            const size_t index = y * WIDTH + x;
            buffer[index] = vga_entry(' ', current_color);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void Video::putchar(char c, uint8_t color) 
{
    switch (c) 
    {
        case '\n':
            cursor_x = 0;
            cursor_y++;
            break;

        case '\t':
            cursor_x = (cursor_x + 4) & ~(4 - 1);
            break;

        case '\b':
            if (cursor_x > 0) cursor_x--;
            break;

        default:
            const size_t index = cursor_y * WIDTH + cursor_x;
            buffer[index] = vga_entry(c, color);
            cursor_x++;
            break;
    }
    check_bounds();
}

void Video::print(const char* str, uint8_t color) 
{
    while (*str) 
    {
        putchar(*str++, color);
    }
}

void Video::set_cursor(size_t x, size_t y) {
    cursor_x = x;
    cursor_y = y;
    check_bounds();
}

uint8_t Video::vga_color(uint8_t fg, uint8_t bg) 
{
    return fg | (bg << 4);
}

void Video::check_bounds() 
{
    if (cursor_x >= WIDTH) 
    {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= HEIGHT) 
    {
        for (size_t y = 1; y < HEIGHT; y++) 
        {
            for (size_t x = 0; x < WIDTH; x++) 
            {
                buffer[(y - 1) * WIDTH + x] = buffer[y * WIDTH + x];
            }
        }

        for (size_t x = 0; x < WIDTH; x++) 
        {
            buffer[(HEIGHT - 1) * WIDTH + x] = vga_entry(' ', current_color);
        }
        cursor_y = HEIGHT - 1;
    }
}

uint16_t Video::vga_entry(char c, uint8_t color)
{
    return static_cast<uint16_t>(c) | static_cast<uint16_t>(color) << 8;
}
