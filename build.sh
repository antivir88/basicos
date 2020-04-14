#!/bin/bash

# remove files
rm -rf .build

# make buid dir
mkdir .build

# compile files
nasm -f elf32 boot.asm -o .build/boot.o
gcc -m32 -ffreestanding -fno-stack-protector -nostdlib -c kmain.c -o .build/kmain.o

# linking
ld -m elf_i386 -T kernel.ld -o .build/os.elf .build/boot.o .build/kmain.o

# objecting
objcopy -O binary .build/os.elf .build/iso.bin

# make grub
mkdir .build/iso
mkdir .build/iso/boot
mkdir .build/iso/boot/grub
cp grub.cfg .build/iso/boot/grub/grub.cfg
cp .build/os.elf .build/iso/boot/kernel.bin
grub2-mkrescue -o .build/basic-os.iso .build/iso

# running without grub
#qemu-system-x86_64 -kernel .build/os.elf

# running via grub
qemu-system-x86_64 -cdrom .build/basic-os.iso

