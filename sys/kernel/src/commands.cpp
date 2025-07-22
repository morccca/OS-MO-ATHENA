#include "../include/commands.h"

void Commands::execute(const char* command) 
{
    if (compare(command, "help")) 
    {
        help();
    }
    else if (compare(command, "clear")) 
    {
        clear();
    }
    else if (compare(command, "about")) 
    {
        about();
    }
    else if (compare(command, "reboot")) 
    {
        reboot();
    }
    else if (starts_with(command, "echo ")) 
    {
        echo(command + 5);
    }
    else if (starts_with(command, "color ")) 
    {
        color(command + 6);
    }
    else 
    {
        print_error("Unknown command. Type 'help' for available commands.");
    }
}


void Commands::help() 
{
    Video::print("=== Athena OS Help ===\n", HEADER_COLOR);

    Video::print(
        "help           - Show this help\n"
        "clear          - Clear screen\n"
        "about          - System info\n"
        "reboot         - Restart system\n"
        "echo <text>    - Print text\n"
        "color <fg> <bg> - Set colors (0-15)\n"
        "color list     - Show color palette\n",
        TEXT_COLOR
    );
}

void Commands::clear() 
{
    Video::clear();
}

void Commands::about() 
{
    Video::print("=== System Info ===\n", HEADER_COLOR);

    Video::print(
        "OS: Athena OS\n"
        "Version: 1.0\n"
        "Mode: 32-bit Protected\n"
        "Video: VGA 80x25\n"
        "Keyboard: SHIFT support\n",
        TEXT_COLOR
    );
}

void Commands::reboot() 
{
    Video::print("Rebooting...\n", ERROR_COLOR);

    Ports::outb(0x64, 0xFE); // Команда перезагрузки
    while(1); // Зависаем, если не сработало
}

void Commands::echo(const char* text) 
{
    Video::print(text, TEXT_COLOR);
    Video::putchar('\n');
}

void Commands::color(const char* args) 
{
    if (compare(args, "list")) 
    {
        show_colors();
        return;
    }
    
    // Парсим два числа: fg bg
    int fg = 0, bg = 0;
    int parsed = 0;
    
    // Простой парсинг чисел
    const char* ptr = args;
    while (*ptr == ' ') ptr++; // Пропускаем пробелы
    
    // Парсим первое число (fg)
    while (*ptr >= '0' && *ptr <= '9') 
    {
        fg = fg * 10 + (*ptr - '0');
        ptr++;
        parsed = 1;
    }
    
    while (*ptr == ' ') ptr++; // Пропускаем пробелы
    
    // Парсим второе число (bg)
    while (*ptr >= '0' && *ptr <= '9') 
    {
        bg = bg * 10 + (*ptr - '0');
        ptr++;
        parsed = 2;
    }
    
    if (parsed < 2) 
    {
        print_error("Usage: color <fg> <bg> (0-15) or 'color list'");
        return;
    }
    
    if (fg < 0 || fg > 15 || bg < 0 || bg > 15) 
    {
        print_error("Colors must be 0-15");
        return;
    }
    
    // Устанавливаем новые цвета
    extern uint8_t TEXT_COLOR;
    extern uint8_t HEADER_COLOR;
    
    TEXT_COLOR = Video::vga_color(fg, bg);
    HEADER_COLOR = Video::vga_color(fg == 14 ? 15 : 14, bg); // Контрастный заголовок
    
    Video::print("Colors changed!\n", TEXT_COLOR);
}

void Commands::show_colors() 
{
    Video::print("=== Color Palette ===\n", HEADER_COLOR);
    
    const char* color_names[] = {
        "0-Black", "1-Blue", "2-Green", "3-Cyan",
        "4-Red", "5-Magenta", "6-Brown", "7-LightGray",
        "8-DarkGray", "9-LightBlue", "10-LightGreen", "11-LightCyan",
        "12-LightRed", "13-Pink", "14-Yellow", "15-White"
    };
    
    for (int i = 0; i < 16; i++) 
    {
        uint8_t color = Video::vga_color(15, i); // Белый текст на цветном фоне
        Video::print(color_names[i], color);
        Video::print("  ", DEFAULT_COLOR);
        
        if ((i + 1) % 4 == 0) Video::putchar('\n');
    }
    Video::putchar('\n');
    Video::print("Usage: color <fg> <bg>\n", TEXT_COLOR);
}

////////////////////////////////////////

bool Commands::compare(const char* s1, const char* s2) 
{
    while (*s1 && *s2 && *s1 == *s2) { s1++; s2++; }
    return *s1 == *s2;
}

bool Commands::starts_with(const char* str, const char* prefix) {
    while (*prefix) if (*prefix++ != *str++) return false;
    return true;
}

void Commands::print_error(const char* msg) {
    Video::print(msg, ERROR_COLOR);
    Video::putchar('\n');
}