BUILDDIR = .build

rebuild: clean asm source linking objecting makeiso
rerunraw: rebuild runraw
reruniso: rebuild runiso


asm:
	nasm -f elf32 src/asm/boot.asm -o $(BUILDDIR)/boot.o
	nasm -f elf32 src/asm/gdt.asm -o $(BUILDDIR)/gdt.o
	nasm -f elf32 src/asm/proc.asm -o $(BUILDDIR)/proc.o
	nasm -f elf32 src/asm/irqs.asm -o $(BUILDDIR)/irqs.o

source:
	gcc -m32 -ffreestanding -fno-stack-protector -Wall -Wextra -nostdlib -nostdinc -fno-builtin -c src/kmain.c -o $(BUILDDIR)/kmain.o

linking:
	ld -m elf_i386 -T kernel.ld -o $(BUILDDIR)/os.elf $(BUILDDIR)/boot.o $(BUILDDIR)/gdt.o $(BUILDDIR)/proc.o $(BUILDDIR)/irqs.o $(BUILDDIR)/kmain.o

objecting:
	objcopy -O binary $(BUILDDIR)/os.elf $(BUILDDIR)/iso.bin

makeiso:
	mkdir -p $(BUILDDIR)/iso/boot/grub
	cp grub.cfg $(BUILDDIR)/iso/boot/grub/grub.cfg
	cp $(BUILDDIR)/os.elf $(BUILDDIR)/iso/boot/kernel.bin
	grub2-mkrescue -o $(BUILDDIR)/basic-os.iso $(BUILDDIR)/iso


runraw:
	qemu-system-x86_64 -kernel $(BUILDDIR)/os.elf
runiso:
	qemu-system-x86_64 -cdrom $(BUILDDIR)/basic-os.iso


clean:
	rm -rf $(BUILDDIR)/*
