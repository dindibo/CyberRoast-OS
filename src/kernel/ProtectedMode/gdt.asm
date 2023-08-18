global gdt_write
global read_cr0

gdt_write:
	mov eax, [esp+4]
	lgdt [eax]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush
flush:
		ret

read_cr0:
	mov eax, cr0
	ret
