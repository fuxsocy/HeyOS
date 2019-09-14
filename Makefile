CXX = g++
CXXFLAGS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin\
	   -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings

AS = nasm
ASFLAGS = -f elf32

LD = ld
LDFLAGS = -T linker.ld -melf_i386


BUILD = build
OS_NAME = HeyOS
SRC_CPP = $(wildcard **/*.cc)
SRC_ASM = $(wildcard **/*.S)
OBJECTS = $(wildcard **/*.o) $(wildcard *.o)


all:
	@# Perform out-of-place build
	mkdir -p $(BUILD)
	@# Assemble each .S into .o
	$(foreach o, $(SRC_ASM), $(AS) $(ASFLAGS) $(o))
	@# Compile each .cc into .o
	$(CXX) $(CXXFLAGS) -c $(SRC_CPP)
	@# Link all .o into ELF executable
	make HeyOS

HeyOS:
	$(LD) $(LDFLAGS) -o $(BUILD)/$(OS_NAME) $(OBJECTS)

iso:
	mkdir -p iso
	mkdir -p iso/boot
	mkdir -p iso/boot/grub
	cp $(BUILD)/$(OS_NAME) iso/boot/$(OS_NAME)
	@echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	@echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	@echo ''                                  >> iso/boot/grub/grub.cfg
	@echo 'menuentry "$(OS_NAME)" {' 		  >> iso/boot/grub/grub.cfg
	@echo '  multiboot /boot/$(OS_NAME)'           >> iso/boot/grub/grub.cfg
	@echo '  boot'                            >> iso/boot/grub/grub.cfg
	@echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(BUILD)/$(OS_NAME).iso iso
	rm -rf iso

run:
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm '$(OS_NAME)' &

clean:
	find . -type f -iname "*.o" | xargs rm
	rm -rf $(BUILD)
	rm -rf iso
