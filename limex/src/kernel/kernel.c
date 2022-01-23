#include "framebuffer/framebuffer.h"
#include "drivers/keyboard/ps2.h"
#include "sys/scheduler/rtc.h"
#include "terminal/terminal.h"
#include "kernel/kernel.h"
#include "sys/cpu/idt.h"
#include "std/printf.h"
#include "std/stdlib.h"
#include "stivale2.h"

uint8_t stack[8192];

struct stivale2_struct_tag_framebuffer* framebuffer_tag;
struct stivale2_struct_tag_terminal* terminal_tag;
struct stivale2_struct_tag_epoch* epoch_tag;

static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },
    .flags = 0
};

static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_hdr_tag
    },
    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};

__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
    .tags = (uintptr_t)&framebuffer_hdr_tag
};

void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
    struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
    for (;;) {
        if (current_tag == NULL) {
            return NULL;
        }

        if (current_tag->identifier == id) {
            return current_tag;
        }

        current_tag = (void *)current_tag->next;
    }
}

void _start(struct stivale2_struct *stivale2_struct) {
    terminal_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    epoch_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_EPOCH_ID);
    framebuffer_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    init_terminal();
    print_status("Terminal Initialized", SUCCESS, 0);

    print_status("Initializing Framebuffer", INFO, 0);
    init_framebuffer();
    print_status("Framebuffer Initialized", SUCCESS, 1);

    print_status("Initializing IDT", INFO, 0);
    idt_init();
    print_status("IDT Initialized", SUCCESS, 1);

    for(;;) {
        char character = nonblocking_getchar();

        if(character != 0) {
            char offset = 0;

            if(is_shift_down() && character >= 97 && character <= 122) {
                offset = -32;
            }

            if(character == 56) {
                cursor_up(1);
            } else {
                putchar_(character + offset);

                //printf("%d", (int)character);

                if(character == 8) {
                    print(" \b");
                }
            }
        }
    }
}
