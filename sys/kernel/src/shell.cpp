#include "shell.h"

int string_compare(const char* str1, const char* str2) 
{
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

uint8_t PROMPT_COLOR = Video::vga_color(static_cast<uint8_t>(graphics::Color::LIGHT_CYAN), static_cast<uint8_t>(graphics::Color::BLACK));
uint8_t TEXT_COLOR = Video::vga_color(static_cast<uint8_t>(graphics::Color::LIGHT_GREEN), static_cast<uint8_t>(graphics::Color::BLACK));
uint8_t HEADER_COLOR = Video::vga_color(static_cast<uint8_t>(graphics::Color::YELLOW), static_cast<uint8_t>(graphics::Color::BLACK));

void Shell::run() 
{
    Video::clear();
    Video::print("Athena OS v1.0 - Protected Mode\n", HEADER_COLOR);
    Video::print("Type 'help' for commands\n\n", TEXT_COLOR);

    while (true) 
    {
        show_prompt();
        char command[256];
        int len = read_input(command, sizeof(command));
        if (len > 0) 
        {
            execute_command(command);
        }
    }
}

void Shell::show_prompt() 
{
    Video::print("> ", PROMPT_COLOR);
}

int Shell::read_input(char* buffer, int max_len) 
{
    int pos = 0;

    while (true) 
    {
        char c = Keyboard::getchar();
        
        if (c == '\n') 
        {
            Video::putchar('\n', TEXT_COLOR);
            buffer[pos] = '\0';
            return pos;
        }
        
        if (c == '\b' && pos > 0) 
        {
            Video::putchar('\b', TEXT_COLOR);
            Video::putchar(' ', TEXT_COLOR);
            Video::putchar('\b', TEXT_COLOR);
            pos--;
            continue;
        }
        
        if (c >= 32 && pos < max_len - 1) 
        {
            Video::putchar(c, TEXT_COLOR);
            buffer[pos++] = c;
        }
    }
}

void Shell::execute_command(const char* command) 
{
    if (string_compare(command, "help") == 0) 
    {
        Video::print("Available commands: help, clear, about\n", TEXT_COLOR);
    }
    else if (string_compare(command, "clear") == 0) 
    {
        Video::clear();
    }
    else if (string_compare(command, "about") == 0) 
    {
        Video::print("Athena OS - A simple operating system\n", TEXT_COLOR);
    }
    else 
    {
        Video::print("Unknown command. Type 'help' for help.\n", TEXT_COLOR);
    }
}
