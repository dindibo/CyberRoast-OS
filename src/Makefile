CC:=i686-elf-gcc
CFLAGS:=-c -Wall
LD:=i686-elf-ld
LDFLAGS:=-T linker.ld -o kernel.bin

all: kernel.o boot.o
	$(LD) $(LDFLAGS) kernel.o boot.o screen.o gdt_int.o descriptors.o vgaapi.o regs.o tst.o

kernel.o: vgaapi.o screen.o descriptors.o regs.o
	$(CC) $(CFLAGS) kernel/kernel.c

descriptors.o: gdt_int.o
	$(CC) $(CFLAGS) kernel/descriptors.c

screen.o:
	$(CC) $(CFLAGS) kernel/screen.c

vgaapi.o:
	$(CC) $(CFLAGS) kernel/TermIo/vgaapi.c

clean:
	$(shell rm -rf *.o kernel.bin)
