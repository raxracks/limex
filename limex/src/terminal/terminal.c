#include "terminal/terminal.h"
#include "kernel/kernel.h"
#include "std/printf.h"
#include "std/string.h"

void (*terminal_write)(const char *, uint64_t);

void init_terminal() {
    void *term_write_ptr = (void *)terminal_tag->term_write;
    terminal_write = term_write_ptr;
}

void print(char* string) {
    terminal_write(string, strlen(string));
}

void println(char* string) {
    print(string);
    print("\n");
}

void set_color(char* color) {
    print(color);
}

void cursor_up(int lines)
{
    printf("\033[%dA", lines);
}

void cursor_down(int lines)
{
    printf("\033[%dB", lines);
}

void cursor_right(int spaces)
{
    printf("\033[%dC", spaces);
}

void cursor_left(int space)
{
    printf("\033[%dD", space);
}

void print_status(char* text, int level, int go_up) {
    switch (level) {
        case 0:
            if(go_up == 1) cursor_up(1);
            
            printf("%s[%s.%s] %s                                   \n", WHITE, BLUE, WHITE, text);
            break;
        case 1:
            if(go_up == 1) cursor_up(1);

            printf("%s[%s*%s] %s                                   \n", WHITE, GREEN, WHITE, text);
            break;
        case 2:
            if(go_up == 1) cursor_up(1);

            printf("%s[%s*%s] %s                                   \n", WHITE, YELLOW, WHITE, text);
            break;
        case 3:
            if(go_up == 1) cursor_up(1);

            printf("%s[%s*%s] %s                                   \n", WHITE, RED, WHITE, text);
            break;
        case 4:
            break;
    }
}

void putchar_(char character)
{
    terminal_write(&character, 1);
}