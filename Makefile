BINARY=os.bin

CCPATH=~/opt/cross/bin
CC=i686-elf-gcc
OPT=-O2
CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra
LINKERFLAGS=-ffreestanding -nostdlib -lgcc

all: $(BINARY)
	@echo "done :)"

$(BINARY): kernel.o linker.ld
	
kernel.o: kernel.c
	@echo "** Building kernel"
	@$(CCPATH)/$(CC) -c kernel.c -o kernel.o $(CFLAGS) $(OPT)

linker.ld: boot.o kernel.o
	@echo "** Linking"
	@$(CCPATH)/$(CC) -T linker.ld -o $(BINARY) $(LINKERFLAGS) $(OPT) boot.o kernel.o

iso:
	grub-mkrescue isodir/ -o os.bin isodir/	
clean:
	rm -rf $(BINARY) kernel.o
