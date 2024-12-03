.intel_syntax noprefix

.text
.global set_interrupt_register
set_interrupt_register:
    push ebp
    mov ebp, esp
    mov esi, dword ptr [ebp+12]
    mov esp, ebp
    pop ebp
    ret