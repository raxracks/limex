#ifndef PS2_KEYBOARD_H
#define PS2_KEYBOARD_H

#include <stdint.h>

// void getline(char* string, int len);
char getchar();
char nonblocking_getchar();
int is_shift_down();

#endif