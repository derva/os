.intel_syntax noprefix

.section .text
.global gdt_flush
.extern gdt_ptr

gdt_flush:
    lgdt [gdt_ptr]
    mov %ax, 0x10
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    jmp 0x08:flush2          # Jump to flush2 with the code segment selector

flush2:
    ret                       # Return from the function
