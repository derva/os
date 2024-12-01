#include "../include/gdt.h"

struct gdt_segment gdt_entries[3];
struct gdt_ptr_struct gdt_ptr;

void initSegment(int num, uint32_t limit, uint32_t base, uint8_t access, uint8_t gran) {
	gdt_entries[num].limit_low = limit &  0xFFFF;
	gdt_entries[num].base_low = base & 0xFFFF;
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
	gdt_entries[num].access = access;
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;
	gdt_entries[num].granularity |= (gran & 0xF0);
}

void initGdt() {
	gdt_ptr.limit = (sizeof(struct gdt_segment) * 3) - 1;
	gdt_ptr.base = (unsigned int)gdt_entries;

	initSegment(0, 0, 0, 0, 0);
	initSegment(1, 0xFFFFFFFF, 0, 0x9A, 0xCF); //kernel code segment
	initSegment(2, 0xFFFFFFFF, 0, 0x92, 0xCF); //kernel data segment
	//initSegment(3, 0xFFFFFFFF, 0, 0xFA, 0xCF); //user code
	//initSegment(4, 0xFFFFFFFF, 0, 0xF2, 0xCF); //user code
	
	gdt_flush();
}
