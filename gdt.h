#include<stdint.h>

//8 bytes long
struct gdt_segment {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t base_high;
	uint8_t access;
	uint8_t granularity;
} __attribute__((packed));

struct gdt_ptr_struct {
	unsigned short limit;
	//unsigned int base;
	//struct gdt_segment*  base;
	unsigned int base;
} __attribute__((packed));

struct gdt_flag{};

void initSegment(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void initGdt();

//extern void gdt_flush(void* gdt_ptr);
extern void gdt_flush();