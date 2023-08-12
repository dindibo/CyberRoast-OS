global read_cr0
global foo

read_cr0:
    push    ebp
    mov     ebp, esp

    mov eax, cr0

    leave
    ret

foo:
    push    ebp
    mov     ebp, esp

    mov eax, 0xdeadbeef

    leave
    ret