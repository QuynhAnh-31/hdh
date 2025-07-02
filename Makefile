kkCXX=i686-elf-g++
LD=ld
CXXFLAGS=-ffreestanding -m32 -Wall -Wextra

all: os-image.iso

kernel.o: kernel.cpp io.hpp
	$(CXX) $(CXXFLAGS) -c kernel.cpp -o kernel.o

io.o: io.cpp io.hpp
	$(CXX) $(CXXFLAGS) -c io.cpp -o io.o

kernel.bin: kernel.o io.o linker.ld
	$(LD) -m elf_i386 -T linker.ld -o kernel.bin kernel.o io.o

os-image.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'menuentry "MiniOS" { multiboot /boot/kernel.bin }' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o os-image.iso iso

run: os-image.iso
	qemu-system-i386 -cdrom os-image.iso

clean:
	rm -rf *.o *.bin *.iso iso
