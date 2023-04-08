extern putc

putc:

push ebp
mov ebp, esp

mov ah, 0x0e    ; function number = 0Eh : Display Character
mov al, '!'     ; AL = code of character to display
int 0x10        ; call INT 10h, BIOS video service

pop ebp
ret
