BINARY=os.bin

CCPATH=~/opt/cross/bin
CC=i686-elf-gcc
ASM=i686-elf-as
OPT=-O2
CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra
LINKERFLAGS=-ffreestanding -nostdlib -lgcc

all: $(BINARY)
	@echo "done :)"

$(BINARY): kernel.o gdt.o gdts.o linker.ld
	
kernel.o: kernel.c
	@echo "** Building kernel"
	@$(CCPATH)/$(CC) -c kernel.c -o kernel.o $(CFLAGS) $(OPT)

gdt.o: gdt.c
	@echo "** Building gdt.c"
	@$(CCPATH)/$(CC) -c gdt.c -o gdt.o $(CFLAGS) $(OPT)


gdts.o: gdt.asm
	@echo "** Building assembler code"
	@$(CCPATH)/$(ASM) gdt.asm -o gdts.o

linker.ld: boot.o kernel.o gdts.o gdt.o
	@echo "** Linking"
	$(CCPATH)/$(CC) -T linker.ld -o $(BINARY) $(LINKERFLAGS) $(OPT) boot.o gdt.o gdts.o kernel.o

iso:
	grub-mkrescue isodir/ -o os.bin isodir/	
clean:
	rm -rf $(BINARY) kernel.o
