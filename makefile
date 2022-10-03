GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-stack-protector -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

# 目标来自cpp文件或s文件
objects = $(patsubst %.cpp, %.o, $(wildcard *.cpp)) $(patsubst %.s, %.o, $(wildcard *.s))



%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)


mykernel.iso: mykernel.bin
	mkdir -p iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My OS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

build: mykernel.iso

clean:
	rm -rf *.o mykernel.bin

run: build
	qemu-system-i386 \
		mykernel.iso

.PHONY: run clean build

