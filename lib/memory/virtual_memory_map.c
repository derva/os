#include "virtual_memory_map.h"

page_directory* current_page_dir = 0;

pd_entry* get_pd_entry(page_directory *pd, virtual_address address) {
	if (pd) {
		return &pd->entries[PT_INDEX(address)];
	}
	return 0;
}

pt_entry* get_pt_entry(page_table *pt, virtual_address address) {
	if (pt) {
		return &pt->entries[PT_INDEX(address)];
	}
	return 0;
}

pt_entry* get_page(const virtual_address address) {

	page_directory* pd = current_page_dir;
	pd_entry* entry = &pd->entries[PD_INDEX(address)];
	page_table* table = (page_table *)PAGE_PHYS_ADDRESS(entry);

	pt_entry* page = &table->entries[PT_INDEX(address)];

	return page;
}

//for start it will work only for one page table
pt_entry* find_first_free_page() {
	page_directory *pd = current_page_dir;
	virtual_address address = 0;

	//find entry in page directory
	for (uint16_t i = 0; i < TABLES_PER_DIRECTORY; i++) {
		pd_entry *entry = &pd->entries[PD_INDEX(address)];
		for (uint16_t i = 0; i < 1024; i++) {
			page_table *page_tbl = (page_table *)PAGE_PHYS_ADDRESS(entry);
			//now we need to test inside one page table each entry if it's free
			for (int i = 0; i < PAGES_PER_TABLE; i++) {
				if (!(page_tbl->entries[i] & PTE_PRESENT)) {
					//this page table entry is empty
					return page_tbl->entries[i];
				}
			}
		}
		entry += (PAGE_SIZE * PAGES_PER_TABLE);
	}
	//return -1; //error
}

void* allocate_page() {
	pt_entry* address = find_first_free_page();
	SET_ATTRIBUTE(address, PTE_PRESENT);
	return *address;

}

void* deallocate_page(virtual_address address) {
	SET_ATTRIBUTE(&address, !PTE_PRESENT);
	//add check if it succeed
	return;
}

void initialize_virtual_memory() {

}

init_physical_memory
