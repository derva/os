#ifndef PMM_H
#define PMM_H
#define BIT_COLUMN  12
#define BIT_ROW     12


/* 
PMM is responsible to keep track which parts of physical memory are being taken or freed.
*/
void initPMM(struct multiboot_info* mbt);
void initBitmask();
#endif