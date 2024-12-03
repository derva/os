#pragma once
#include<stdint.h>
#include "kernel.h"

#define PAGES_PER_TABLE 1024
#define TABLES_PER_DIRECTORY 1024
#define PAGE_SIZE 4069


extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

void* allocate_page();
//void* deallocate_page(virtual_address address);
void init_paging();