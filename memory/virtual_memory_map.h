#pragma once
#include<stdint.h>

#define PAGES_PER_TABLE 1024
#define TABLES_PER_DIRECTORY 1024
#define PAGE_SIZE 4069

#define PT_INDEX(address) ((address >> 12) & 0x3FF)
#define PD_INDEX(address) ((address) >> 22 )
#define PAGE_PHYS_ADDRESS(dir_entry) ((*dir_entry) & ~0xFFF)
#define SET_ATTRIBUTE(entry, attr) (*entry |= attr)

typedef uint32_t pd_entry;
typedef uint32_t pt_entry;
typedef uint32_t virtual_address;
typedef uint32_t physical_address;

typedef enum {
	PTE_PRESENT       = 0x01,
	PTE_READ_WRITE    = 0x02,
	PTE_USER          = 0x04,
	PTE_WRITE_THROUGH = 0x08,
	PTE_CACHE_DISABLE = 0x10,
	PTE_ACCESSED      = 0x20,
	PTE_DIRTY         = 0x40,
	PTE_PAT           = 0x80,
	PTE_GLOBAL        = 0x100,
	PTE_FRAME         = 0x7FFFF000,   // bits 12+
} PAGE_TABLE_FLAGS;

typedef enum {
	PDE_PRESENT       = 0x01,
	PDE_READ_WRITE    = 0x02,
	PDE_USER          = 0x04,
	PDE_WRITE_THROUGH = 0x08,
	PDE_CACHE_DISABLE = 0x11,
	PDE_ACCESSED      = 0x21,
	PDE_DIRTY         = 0x41,          // 4MB entry only
	PDE_PAGE_SIZE     = 0x81,          // 0 = 4KB page, 1 = 4MB page
	PDE_GLOBAL        = 0x101,         // 4MB entry only
	PDE_PAT           = 0x2000,        // 4MB entry only
	PDE_FRAME         = 0x7FFFF000,    // bits 12+
} PAGE_DIR_FLAGS;

typedef struct {
	pt_entry entries[PAGES_PER_TABLE];
} page_table;

typedef struct {
	pd_entry entries[TABLES_PER_DIRECTORY];
} page_directory;



pd_entry* get_pd_entry(page_directory *pd, virtual_address address);
pt_entry* get_pt_entry(page_table *pt, virtual_address address);
pt_entry* get_page(const virtual_address address);
pt_entry* find_first_free_page();

void* allocate_page();
void* deallocate_page(virtual_address address);