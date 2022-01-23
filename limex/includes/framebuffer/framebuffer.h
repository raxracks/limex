#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

void init_framebuffer();
void framebuffer_pixel(int x, int y, uint32_t color);

#endif