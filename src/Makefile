CC:=i686-elf-gcc
CFLAGS:=-c -Wall
LD:=i686-elf-ld
LDFLAGS:=-T linker.ld -o kernel.bin

all: kernel.o boot.o
	$(LD) $(LDFLAGS) kernel.o boot.o screen.o gdt_int.o vgaapi.o regs.o tst.o descriptors.o idt.o isr.o asmisr.o

kernel.o: vgaapi.o screen.o regs.o descriptors.o idt.o isr.o asmisr.o tst.o
	$(CC) $(CFLAGS) kernel/kernel.c

screen.o:
	$(CC) $(CFLAGS) kernel/screen.c

vgaapi.o:
	$(CC) $(CFLAGS) kernel/TermIo/vgaapi.c

descriptors.o:
	$(CC) $(CFLAGS) kernel/descriptors.c

isr.o:
	$(CC) $(CFLAGS) kernel/isr.c

clean:
	$(shell rm -rf *.o kernel.bin)
