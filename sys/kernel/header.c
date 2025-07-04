char *vidmem = (char*)0xb8000; // ячейка для сохранения
int cursor_x = 0, cursor_y = 0;

/////////////// ФУНКЦИИ
void scrollScreen();
void printChar(char c);
void printString(const char* str);
void printColorString(const char* str, char color);


void scrollScreen() 
{
    int i;

    for(i = 0; i < 24 * 80 * 2; i++) 
    {
        vidmem[i] = vidmem[i + 80 * 2];
    }
    for(i = 24 * 80 * 2; i < 25 * 80 * 2; i += 2) 
    {
        vidmem[i] = ' ';
        vidmem[i + 1] = 0x07;
    }
}

void clearScreen() 
{
    unsigned int j = 0;

    while(j < 80*25*2) // размер окна
    {
        vidmem[j] = ' ';
        vidmem[j+1] = 0x07;
        j += 2;
    }
    cursor_x = cursor_y = 0;
}

void printChar(char c) 
{
    if(c == '\n') 
    {
        cursor_x = 0;
        cursor_y++;
        if(cursor_y >= 25) 
        {
            cursor_y = 24;
            scrollScreen();
        }
    } 
    else if(c == '\b') 
    {
        if(cursor_x > 0) 
            cursor_x--;
    } 
    else 
    {
        int pos = (cursor_y * 80 + cursor_x) * 2;

        vidmem[pos] = c;
        vidmem[pos + 1] = 0x07;

        cursor_x++;

        if(cursor_x >= 80) 
        {
            cursor_x = 0;
            cursor_y++;
            if(cursor_y >= 25) 
            {
                cursor_y = 24;
                scrollScreen();
            }
        }
    }
}

void printString(const char* str) 
{
    while(*str) 
    {
        printChar(*str);
        str++;
    }
}

void printColorString(const char* str, char color) 
{
    while(*str) 
    {
        if(*str == '\n') 
        {
            cursor_x = 0;
            cursor_y++;
            if(cursor_y >= 25) 
            {
                cursor_y = 24;
                scrollScreen();
            }
        } 
        else 
        {
            int pos = (cursor_y * 80 + cursor_x) * 2;

            vidmem[pos] = *str;
            vidmem[pos + 1] = color;
            cursor_x++;

            if(cursor_x >= 80) 
            {
                cursor_x = 0;
                cursor_y++;
                if(cursor_y >= 25) 
                {
                    cursor_y = 24;
                    scrollScreen();
                }
            }
        }

        str++;
    }
}

//вспомогающие функции
unsigned char inb(unsigned short port) 
{
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void outb(unsigned short port, unsigned char data) 
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

char keyboard_map[128] = // клава
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char get_key() 
{
    unsigned char status;
    char keycode;
    
    do 
    {
        status = inb(0x64);
    } while (!(status & 0x01));
    
    keycode = inb(0x60);
    
    // игнор отпускание клавиш 
    if(keycode & 0x80) 
    return 0;  // отпускание клавиши
    
    if(keycode < 0 || keycode >= 128) return 0;
    
    return keyboard_map[keycode];
}

int strlen(const char* str) 
{
    int len = 0;
    while(str[len]) len++;
    return len;
}

int strcmp(const char* str1, const char* str2) 
{
    while(*str1 && (*str1 == *str2)) 
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void reboot() {
    outb(0x64, 0xFE);
}

// Лого
void show_athena_help() 
{
    clearScreen();
    
    
    printColorString("                    /\\\n", 0x0B);
    printColorString("                   /  \\\n", 0x0B);
    printColorString("                  / /\\ \\\n", 0x0B);
    printColorString("                 / /  \\ \\\n", 0x0B);
    printColorString("                / /____\\ \\\n", 0x0B);
    printColorString("               / /      \\ \\\n", 0x0B);
    printColorString("              / /  ATHENA \\ \\\n", 0x0E);
    printColorString("             / /____________\\ \\\n", 0x0B);
    printColorString("            /_/              \\_\\\n", 0x0B);
    printColorString("           |  GODDESS OF WISDOM  |\n", 0x0A);
    printColorString("           |____________________|\n\n", 0x0A);
    
    // Описание системы
    printColorString("=== ATHENA OS - OPERATING SYSTEM ===\n", 0x0F);
    printString("Goddess of wisdom, warfare, and handicraft\n");
    printString("Simple x86 Operating System written in Assembly & C\n");
    printString("Created by: Morcc | Version: 1.0.0\n\n");
    
    // Список команд
    printColorString("AVAILABLE COMMANDS:\n", 0x0E);
    printColorString("  help     ", 0x0A);
    printString("- Show this help screen with Athena's wisdom\n");
    printColorString("  clear    ", 0x0A);
    printString("- Clear the screen\n");
    printColorString("  about    ", 0x0A);
    printString("- Display system information\n");
    printColorString("  wisdom   ", 0x0A);
    printString("- Get a quote from Athena\n");
    printColorString("  time     ", 0x0A);
    printString("- Show system uptime\n");
    printColorString("  reboot   ", 0x0A);
    printString("- Restart the system\n\n");
    
    printColorString("Press any key to return to shell...", 0x0C);
    
    // Ждем н/ж
    char key;
    do {
        key = get_key();
    } while(key == 0);  // игнор отпускание клавиш 
    
    clearScreen();
}

void show_wisdom() 
{
    printColorString("Athena's Wisdom: ", 0x0E);
    printString("\"Knowledge is the greatest weapon.\"\n");
}

void execute_command(char* cmd) 
{
    if(strcmp(cmd, "help") == 0) 
    {
        show_athena_help();
    }
    else if(strcmp(cmd, "clear") == 0) 
    {
        clearScreen();
    }
    else if(strcmp(cmd, "about") == 0)
    {
        printColorString("ATHENA OS v1.0.0\n", 0x0E);
        printString("Architecture: x86 (32-bit)\n");
        printString("Created by: Morcc\n");
        printString("Simple Operating System inspired by Greek mythology\n");
        printString("Built with Assembly bootloader and C kernel\n");
    }
    else if(strcmp(cmd, "wisdom") == 0) 
    {
        show_wisdom();
    }
    else if(strcmp(cmd, "time") == 0) 
    {
        printString("System uptime: Running since boot\n");
        printString("Athena watches over this system\n");
    }
    else if(strcmp(cmd, "reboot") == 0) 
    {
        printColorString("Rebooting system...\n", 0x0C);
        printString("May Athena guide your next journey!\n");
        reboot();
    }
    else if(strlen(cmd) > 0) 
    {
        printColorString("Unknown command: ", 0x0C);
        printString(cmd);
        printString("\nType 'help' for available commands\n");
    }
}

void shell() 
{
    char command[256];
    int index = 0;
    char key;
    
    printColorString("=== ATHENA OS SHELL v1.0 ===\n", 0x0E);
    printString("Welcome to the realm of wisdom!\n");
    printString("Type 'help' to see Athena's guidance\n\n");
    
    while(1) 
    {
        printColorString("athena> ", 0x0A); //код ст2 книги
        
        index = 0;
        while(1) {
            key = get_key();
            if(key == '\n') 
            {
                command[index] = '\0';
                printChar('\n');
                break;
            } 
            else if(key == '\b' && index > 0) 
            {
                index--;
                printChar('\b');
                printChar(' ');
                printChar('\b');
            } 
            else if(key >= 32 && index < 255) 
            {
                command[index++] = key;
                printChar(key);
            }
        }
        
        execute_command(command);
    }
}

void OSmain(void) 
{  
    clearScreen();
    printColorString("ATHENA OS Loading...\n", 0x0E);
    printString("Initializing wisdom protocols...\n");
    printString("System ready!\n\n");
    shell();
}
