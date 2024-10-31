.section .text
.global gdt_flush
.extern gdt_ptr

gdt_flush:
    lgdt [gdt_ptr]          # Load the GDT pointer
    mov %ax, 0x10             # Move the data segment selector into AX
    mov %ds, %ax               # Set the data segment
    mov %es, %ax               # Set the extra segment
    mov %fs, %ax               # Set the FS segment
    mov %gs, %ax               # Set the GS segment
    mov %ss, %ax               # Set the stack segment
    jmp flush2          # Jump to flush2 with the code segment selector

flush2:
    ret                       # Return from the function
