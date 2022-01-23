#include "sys/cpu/handler.h"
#include "sys/cpu/idt.h"
#include "std/printf.h"

char* err_message[] = {
    "Divide by 0",
    "Reserved",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bounds range exceeded",
    "Invalid Opcode",
    "Device not available",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TSS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "Reserved",
    "x87 FPU error",
    "Alignment check",
    "Machine check",
    "SIMD Floating Point Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void handle_interrupt(interrupt_context_t *irq_context)
{
    // print_stacktrace(irq_context->rip, irq_context->regs.rbp);

	// check which interrupt happened and handle it
	// default: print info and panic
    switch (irq_context->int_no) {
		case 255:
			// spurious interrupt
			break;
		default:
			printf("error code:%d\n", (int)irq_context->err);
			printf("RIP: %x\n", (unsigned int)irq_context->rip);
			printf("RSP: %x\n", (unsigned int)irq_context->rsp);

			//panic(&irq_context->regs, err_message[irq_context->int_no]);
	}
}