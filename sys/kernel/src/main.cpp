#include "../include/video.h"
#include "../include/shell.h"
#include "../include/ports.h"
#include "../include/keyboard.h"

extern "C" void kernel_main() 
{
    Video::initialize();
    Shell::run();
}
