.text
.global loadPageDirectory
.global enablePaging

loadPageDirectory:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax    # Load page directory address from stack argument
    mov %eax, %cr3       # Move address to CR3 register
    mov %ebp, %esp
    pop %ebp
    ret

enablePaging:
    push %ebp
    mov %esp, %ebp
    mov %cr0, %eax
    or $0x80000000, %eax  # Set paging bit (bit 31)
    mov %eax, %cr0
    mov %ebp, %esp
    pop %ebp
    ret
