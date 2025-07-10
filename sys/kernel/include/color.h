#pragma once

typedef unsigned char uint8_t;
typedef unsigned long size_t;

static constexpr uint8_t HEADER_COLOR = 0x0E; 
static constexpr uint8_t TEXT_COLOR = 0x0A;   
static constexpr uint8_t ERROR_COLOR = 0x0C;  
static constexpr uint8_t DEFAULT_COLOR = TEXT_COLOR;

namespace graphics
{
    enum class Color : uint8_t
    {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GRAY = 7,
        DARK_GRAY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        PINK = 13,
        YELLOW = 14,
        WHITE = 15
    };
}
