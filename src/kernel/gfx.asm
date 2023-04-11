vm86_code:
push ebp
mov ebp, esp

pop ebp
ret

extern goto_vm8086:
push 0 
push 0
push 0
push 0
push 0
push 0fffeh
push 20000h
push 0
push vm86
iret
