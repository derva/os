//.intel_syntax noprefix
/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	/* Subtract 8 so that with to 4 byte parameters the stack is
	 * aligned to 16 bytes when kernel_main is called */
	mov $stack_top-8, %esp
	/* push the pointer to the Multiboot infromation structure*/
	push %ebx
	/* push magic value */
	push %eax

	cld /* rquired for the System V 32-bit ABI */
	call kernel_main
	cli
1:	hlt
	jmp 1b

.size _start, . - _start
