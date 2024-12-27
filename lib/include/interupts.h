void init_interrupt();

struct InterruptDescriptor{
	uint16_t offset_low;
	uint16_t segment_selector;
	uint8_t reserved;
	uint8_t type_attributes;
	uint16_t offset_high;
}__attribute__((packed));

struct InterruptDescriptorRegister {
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

typedef struct InterruptDescriptor idt_entry;
typedef struct InterruptDescriptorRegister idt_reg;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
__attribute__((noreturn))
void exception_handler(void);
