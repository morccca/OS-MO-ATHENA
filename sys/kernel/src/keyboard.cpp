#include "../include/keyboard.h"

static constexpr char KEYMAP_NORMAL[] = 
{
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 
    '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 
    'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static constexpr char KEYMAP_SHIFT[] = 
{
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 
    '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '{', '}', '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 
    'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};

// Состояние клавиш-модификаторов
static bool shift_pressed = false;

char Keyboard::getchar() 
{
    while (!(Ports::inb(0x64) & 0x01)) 
    {
        asm volatile("pause");
    }

    return Ports::inb(0x60);  
}

void Keyboard::wait_for_enter() 
{
    char key;
    do 
    {
        key = getchar();
        if (key & 0x80) continue;
    } 
    while (key != 0x1C);  
}

char Keyboard::scancode_to_ascii(uint8_t scancode) 
{
    // Обработка отпускания клавиш
    if (scancode & 0x80) 
    {
        scancode &= 0x7F; // Убираем флаг отпускания
        
        // SHIFT отпущен
        if (scancode == 0x2A || scancode == 0x36) 
        {
            shift_pressed = false;
        }
        return 0;
    }
    
    // Обработка нажатия клавиш
    // SHIFT нажат
    if (scancode == 0x2A || scancode == 0x36) 
    {
        shift_pressed = true;
        return 0;
    }
    
    // Проверяем границы массива
    if (scancode >= sizeof(KEYMAP_NORMAL)) 
    {
        return 0;
    }
    
    // Возвращаем символ в зависимости от состояния SHIFT
    if (shift_pressed) 
    {
        return KEYMAP_SHIFT[scancode];
    } 
    else 
    {
        return KEYMAP_NORMAL[scancode];
    }
}
