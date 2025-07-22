#include "../include/shell.h"
#include "../include/video.h"
#include "../include/commands.h"

uint8_t PROMPT_COLOR = Video::vga_color(static_cast<uint8_t>(graphics::Color::LIGHT_CYAN), static_cast<uint8_t>(graphics::Color::BLACK));

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
            Commands::execute(command);  // Используем Commands класс
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
        uint8_t scancode = Keyboard::getchar();
        char c = Keyboard::scancode_to_ascii(scancode);  // Конвертируем в ASCII
        
        if (c == 0) continue;  // Игнорируем неизвестные коды
        
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
    Commands::execute(command);  // Делегируем Commands классу
}
