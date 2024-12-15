#include "include/kernel.h"
#include "include/interupts.h"

#define NO_INTERRUPT_VECTORS 256

extern void set_interrupt_register(unsigned int i, unsigned int y);

static idt_entry idt[256];

static idt_reg idtr;

void init_interrupt() {
    tws("\nInterrupt\n");
    set_interrupt_register(5, 8);
    tws("\nAfter it\n");
}