#include "framebuffer/framebuffer.h"
#include "kernel/kernel.h"
#include <stdint.h>

uint16_t fb_width = 0;
uint16_t fb_height = 0;
uint16_t fb_pitch = 0;
uint32_t* fb;

void init_framebuffer() {
    fb_width = framebuffer_tag->framebuffer_width;
    fb_height = framebuffer_tag->framebuffer_height;
    fb_pitch = framebuffer_tag->framebuffer_pitch;
    fb = (uint32_t*)framebuffer_tag->framebuffer_addr;
}

void framebuffer_pixel(int x, int y, uint32_t color) {
    fb[y * (fb_pitch / sizeof(uint32_t)) + x] = color;
}