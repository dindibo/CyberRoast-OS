[bits 16]

extern tst_func:
mov eax, 0xdeadbeef
push eax

push  1

extern do_int


do_int:
    mov eax, 0xdeadbeef
    int 0x80

    ret
