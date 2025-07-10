#ifndef SHELL_HPP
#define SHELL_HPP

#include "color.h"
#include "keyboard.h"
#include "video.h"
#include "commands.h"

class Shell 
{
public:

    static void run();

private:

    static void execute_command(const char* command);

    static void show_prompt();

    static int read_input(char* buffer, int max_len);
};

#endif