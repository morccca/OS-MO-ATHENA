#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "color.h"
#include "ports.h"
#include "video.h"

class Commands 
{
public:
    static void execute(const char* command);

private:
    static void help();
    static void clear();
    static void about();
    static void reboot();
    static void echo(const char* text);
    static void color(const char* args);
    static void show_colors();
    
    // Вспомогательные методы
    static bool compare(const char* s1, const char* s2);
    static bool starts_with(const char* str, const char* prefix);
    static void print_error(const char* msg);
    
};

#endif
