#include "../include/virtual_memory_map.h"

unsigned int page_directory[1024] __attribute__((aligned(4096)));
unsigned int page_table[1024] __attribute__((aligned(4096)));

void init_paging() {
	for(int i = 0; i < 1024; i++) {
		page_directory[i] = 0x00000002;
	}

	//we will fill all 1024 entries in the table, mapping 4 megabytes
	for(unsigned int i = 1; i < 1024; i++)
	{
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
	}

	page_directory[0] = ((unsigned int)page_table) | 3;
	
	loadPageDirectory(page_directory);
	enablePaging();
}
