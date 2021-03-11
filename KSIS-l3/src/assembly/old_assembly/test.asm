section .bss
arr resd 10	
buf resb 1		;bufer to print arr

section .data
i dd 0
num dd 67

section .text

global _start

_start:	
	push dword [num]	
	call printNum

	mov eax, 0x1
	mov ebx, 0x0
	int 0x80


; printNum (dword num)
printNum:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov edi, arr
	cld
	.loop1:
		mov ecx, 10
		div ecx			;remainder -> edx, result -> eax
		
		mov [edi], edx
		add edi, 4

		xor edx, edx
		cmp eax, 0
		je .printingCall

		jmp .loop1

	.printingCall:

	push dword [arr]
	call .printAsNum
	push dword [arr+4]
	call .printAsNum
	push dword [arr+8]
	call .printAsNum
	
	mov esp, ebp
	pop ebp
	ret 4 


;prints value from [buf] as a arrber from [0;9]
.printAsNum:	
	mov eax, 0x4
	mov ebx, 0x1
	
	mov ecx, [esp+4]
	mov [buf], ecx
	mov ecx, buf
	add [buf], byte 48

	mov edx, 1
	int 0x80
	ret 4	

