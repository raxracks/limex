#ifndef KERNEL_H
#define KERNEL_H

#include "stivale2.h"

extern uint8_t stack[];

extern struct stivale2_struct_tag_framebuffer* framebuffer_tag;
extern struct stivale2_struct_tag_terminal* terminal_tag;
extern struct stivale2_struct_tag_epoch* epoch_tag;

#endif