BINARY=os.bin
CODEDIRS=. lib
INCDIRS=. ./include/ # can be list
ASDIRS=.

CCPATH=~/opt/cross/bin
CC=i686-elf-gcc
ASM=i686-elf-as
OPT=-O2

# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD
# automatically add the -I onto each include directory
CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
ASFILES=$(foreach D,$(ASDIRS),$(wildcard $(D)/*.s))
# regular expression replacement
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
ASMBS=$(patsubst %.s,%.o,$(ASFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS) $(ASMBS)
	@echo "Linking ... "
	$(CCPATH)/$(CC) -T linker.ld -o $@ -ffreestanding -nostdlib -lgcc $^
	@echo "Done":

# only want the .c file dependency here, thus $< instead of $^.
#
%.o:%.c
	@echo $@ $^
	$(CCPATH)/$(CC) $(CFLAGS) -c -o $@ $<

%.o:%.s
	@echo $@ $^
	$(CCPATH)/$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(ASMBS) $(DEPFILES)

# shell commands are a set of keystrokes away
distribute: clean
	tar zcvf dist.tgz *

# @ silences the printing of the command
# $(info ...) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

run:
	qemu-system-i386 -kernel $(BINARY)

debug:
	qemu-system-i386 -s -S -kernel $(BINARY)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean distribute diff
