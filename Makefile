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
rerunrawhdd: rebuild runraw86
rerunisohdd: rebuild runiso86

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
	gcc $(GCCOPTS) -c $(KERNLDIR)/io.c -o $(BUILDDIR)/io.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/framebuffer.c -o $(BUILDDIR)/framebuffer.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/timer.c -o $(BUILDDIR)/timer.o
	gcc $(GCCOPTS) -c $(KERNLDIR)/keyboard.c -o $(BUILDDIR)/keyboard.o
	gcc $(GCCOPTS) -c $(SHELLDIR)/shell.c -o $(BUILDDIR)/shell.o

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
	qemu-system-i386 -kernel $(BUILDDIR)/os.elf -monitor stdio
runiso86:
	qemu-system-i386 -cdrom $(BUILDDIR)/basic-os.iso
runraw64:
	qemu-system-x86_64 -kernel $(BUILDDIR)/os.elf
runiso64:
	qemu-system-x86_64 -cdrom $(BUILDDIR)/basic-os.iso

runraw86hdd:
	qemu-system-i386 -kernel $(BUILDDIR)/os.elf hdd.qcow2
runiso86hdd:
	qemu-system-i386 -cdrom $(BUILDDIR)/basic-os.iso hdd.qcow2
runraw64hdd:
	qemu-system-x86_64 -kernel $(BUILDDIR)/os.elf hdd.qcow2
runiso64hdd:
	qemu-system-x86_64 -cdrom $(BUILDDIR)/basic-os.iso hdd.qcow2

clean:
	rm -rf $(BUILDDIR)/*

hardmake:
	qemu-img create -f qcow2 hdd.qcow2 10G
hardinfo:
	qemu-img info hdd.qcow2

# sudo -i
# modprobe nbd                      ; activate kernel module
# qemu-nbd -c /dev/nbd0 ./hdd.qcow2 ; enable route to driver
# ...
# fdisk /dev/nbd0                   ; create partion with type fat32_LBA
# mkfs -t vfat /dev/nbd0p1          ; make fat32 fs
# fsck.vfat /dev/nbd0p1             ; check on errors fat32 fs
# ...
# mount -t vfat /dev/nbd0p1 /mnt    ; mount to host system
# ...                             ; any operation on files and directories
# umount /dev/nbd0p1                ; dismount from host system
# qemu-nbd -d /dev/nbd0             ; disable route from driver
# rmmod nbd                         ; disable kernel module







