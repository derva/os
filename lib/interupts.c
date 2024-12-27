#include "include/kernel.h"
#include "include/interupts.h"
#include <stdbool.h>

#define NO_INTERRUPT_VECTORS 256

extern void set_interrupt_register(unsigned int i, unsigned int y);
static bool vectors[256];
extern void* isr_stub_table[];

__attribute__((noreturn))
void exception_handler(void) {
    __asm__ volatile ("cli; hlt");
    while(1){}
}

static idt_entry idt[256];

static idt_reg idtr;

void init_interrupt() {
    tws("\nInterrupt\n");
    //set_interrupt_register(5, 8);
	idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry) * 256 - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
    tws("\nAfter it\n");
}
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
	idt_entry* descriptor = &idt[vector];

	descriptor->offset_low        = (uint32_t)isr & 0xFFFF;
	descriptor->segment_selector	= 0x08;
	descriptor->type_attributes    = flags;
	descriptor->offset_high       = (uint32_t)isr >> 16;
	descriptor->reserved       = 0;
}