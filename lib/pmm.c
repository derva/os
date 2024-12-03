//#include "pmm.h"
#include "include/multiboot.h"
#include "include/kernel.h"
#include <stdint.h>

/*
Each PAGE IS 4kB
*/
#ifndef PAGE
#define PAGE 4096
#endif

#define MAX_NUMBER_PAGES    1048576
#define MAX_NUMBER_TABLES	1024
#define PAGE_SIZE           4096

//Bitmask
//max_num_pages = 131072
static uint8_t physical_memory_map[MAX_NUMBER_PAGES/8];

void set_page_free(uint32_t bit, uint8_t* map) {
	uint32_t byte = bit / 8; //row
	uint32_t bit_num = bit % 8;//column
	map[byte] |= (1 << bit_num);
}

void initPMM(struct multiboot_info* mbt) {
	tws("\nInitializing Physical Memory Manager\n");
	for (unsigned int i = 0; i < mbt->mmap_length; i += sizeof(struct multiboot_mmap_entry)) {
		struct multiboot_mmap_entry *mmt  = (struct multiboot_mmap_entry*)(mbt->mmap_addr+i);
		if (mmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            uint32_t start_page = mmt->addr_low / PAGE_SIZE ;
            uint32_t end_page = (mmt->addr_low + mmt->len_low) / PAGE_SIZE;
            for (uint32_t i = start_page; i < end_page; i++ ) {
                    set_page_free(i, physical_memory_map);
            }
		}
	}
}
