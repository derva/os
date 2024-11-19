BINARY=nos.bin

CCPATH=~/opt/cross/bin
CC=i686-elf-gcc
ASM=i686-elf-as
OPT=-O2
CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra
LINKERFLAGS=-ffreestanding -nostdlib -lgcc

all: $(BINARY)
	echo "done :)"

$(BINARY): kernel.o gdt.o gdts.o linker.ld
	mv $(BINARY) ./bin
	
kernel.o: kernel.c
	echo "** Building kernel"
	@$(CCPATH)/$(CC) -g -c kernel.c -o kernel.o -g $(CFLAGS) $(OPT)
	echo "after building kernel"

gdt.o: gdt.c
	echo "** Building gdt.c"
	@$(CCPATH)/$(CC) -g -c gdt.c -o gdt.o -g $(CFLAGS) $(OPT)


gdts.o: gdt.asm
	echo "** Building assembler code"
	@$(CCPATH)/$(ASM) gdt.asm -o gdts.o

linker.ld: boot1.o kernel.o gdts.o gdt.o
	echo "** Linking"
	$(CCPATH)/$(CC) -T linker.ld -o $(BINARY) $(LINKERFLAGS) $(OPT) boot1.o gdt.o gdts.o kernel.o

iso:
	grub-mkrescue isodir/ -o os.bin isodir/	
clean:
	rm -rf ./bin/$(BINARY) kernel.o
