#include "commands.h"

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
    else 
    {
        print_error("Unknown command. Type 'help' for available commands.");
    }
}


void Commands::help() 
{
    Video::print("=== Athena OS Help ===\n", HEADER_COLOR);

    Video::print(
        "help     - Show this help\n"
        "clear    - Clear screen\n"
        "about    - System info\n"
        "reboot   - Restart system\n"
        "echo <t> - Print text\n"
        "color <f> <b> - Set colors\n",
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
        "Video: VGA 80x25\n",
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