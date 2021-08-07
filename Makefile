ASMDIR = src/asm
BUILDDIR = .build
KERNLDIR = src/kernel
GLIBCDIR = src/libc
SHELLDIR = src/shell

GCCOPTS = -m32 -ffreestanding -fno-stack-protector -Wall -Wextra -nostdlib \
        -nostdinc -fno-builtin -I $(GLIBCDIR)/include -I $(KERNLDIR)/include \
        -I $(SHELLDIR)/include

LDOPTS = $(BUILDDIR)/os.elf \
        $(BUILDDIR)/boot.o \
        $(BUILDDIR)/interrupt.o \
        $(BUILDDIR)/interrupts.o \
        $(BUILDDIR)/gdt.o \
        $(BUILDDIR)/idt.o \
        $(BUILDDIR)/tss.o \
        $(BUILDDIR)/irq.o \
        $(BUILDDIR)/isr.o \
        $(BUILDDIR)/framebuffer.o \
        $(BUILDDIR)/timer.o \
        $(BUILDDIR)/keyboard.o \
        $(BUILDDIR)/shell.o \
        $(BUILDDIR)/kmain.o



# Make commands
rebuild: clean asm source linking objecting makeiso
rerunraw: rebuild runraw86
reruniso: rebuild runiso86
rerunraw64: rebuild runraw64
reruniso64: rebuild runiso64

# ASM processing
asm:
	nasm -f elf32 $(ASMDIR)/boot.asm -o $(BUILDDIR)/boot.o
	nasm -f elf32 $(ASMDIR)/interrupts.asm -o $(BUILDDIR)/interrupt.o

# Clang processing
source:
	mkdir $(BUILDDIR)/lib
	gcc $(GCCOPTS) -c src/kmain.c -o $(BUILDDIR)/kmain.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/interrupts.c -o $(BUILDDIR)/interrupts.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/gdt.c -o $(BUILDDIR)/gdt.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/tss.c -o $(BUILDDIR)/tss.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/irq.c -o $(BUILDDIR)/irq.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/idt.c -o $(BUILDDIR)/idt.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/isr.c -o $(BUILDDIR)/isr.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/framebuffer.c -o $(BUILDDIR)/framebuffer.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/timer.c -o $(BUILDDIR)/timer.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/keyboard.c -o $(BUILDDIR)/keyboard.o
	gcc $(GCCOPTS) -c $(SHELLDIR)/shell.c -o $(BUILDDIR)/shell.o
	#gcc $(GCCOPTS) -c $(KERNLDIR)/io.c -o $(BUILDDIR)/io.o

# mixer
linking:
	ld -m elf_i386 -T kernel.ld -o $(LDOPTS)

# other commands
objecting:
	objcopy -O binary $(BUILDDIR)/os.elf $(BUILDDIR)/iso.bin

makeiso:
	mkdir -p $(BUILDDIR)/iso/boot/grub
	cp grub.cfg $(BUILDDIR)/iso/boot/grub/grub.cfg
	cp $(BUILDDIR)/os.elf $(BUILDDIR)/iso/boot/kernel.bin
	grub2-mkrescue -o $(BUILDDIR)/basic-os.iso $(BUILDDIR)/iso

runraw86:
	qemu-system-i386 -kernel $(BUILDDIR)/os.elf
runiso86:
	qemu-system-i386 -cdrom $(BUILDDIR)/basic-os.iso
runraw64:
	qemu-system-x86_64 -kernel $(BUILDDIR)/os.elf
runiso64:
	qemu-system-x86_64 -cdrom $(BUILDDIR)/basic-os.iso

clean:
	rm -rf $(BUILDDIR)/*
