PROJDIRS := includes kernel boot drivers interrupt memory_management
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.s")
BUILD := build
OBJFILES := $(patsubst %.s,$(BUILD)/%.o,$(ASMFILES)) $(patsubst %.c,$(BUILD)/%.o,$(SRCFILES))
$(BUILD)/%.o: %.s
	i686-elf-as $< -o $@
$(BUILD)/%.o: %.c
	i686-elf-gcc -w -c -Iincludes -Idrivers -Iinterrupt -Imemory_management -std=gnu99 -ffreestanding -O2 -Wall -Wextra $< -o $@
learnOS.bin: $(OBJFILES)
	i686-elf-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(OBJFILES) -lgcc
iso: learnOS.bin
	mkdir -p isodir/boot/grub
	cp learnOS.bin isodir/boot/learnOS.bin
	grub-mkrescue -o learnOS.iso isodir
run: iso
	qemu-system-i386 -cdrom learnOS.iso
clean:
	-rm $(OBJFILES)
	-rm isodir/boot/learnOS.bin
	-rm *.iso
	-rm *.bin