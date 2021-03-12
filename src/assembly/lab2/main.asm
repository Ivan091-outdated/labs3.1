section text
global	replace, @function
replace:
.LFB0:
	push	rbp
	mov	rbp, rsp
	mov	QWORD [rbp-24], rdi
	mov	ecx, esi
	mov	eax, edx
	mov	edx, ecx
	mov	BYTE [rbp-28], dl
	mov	BYTE [rbp-32], al
	mov	rax, QWORD [rbp-24]
	mov	QWORD [rbp-8], rax
	jmp	.L2
.L4:
	mov	rax, QWORD [rbp-8]
	movzx	eax, BYTE [rax]
	cmp	BYTE [rbp-28], al
	jne	.L3
	mov	rax, QWORD [rbp-8]
	movzx	edx, BYTE [rbp-32]
	mov	BYTE [rax], dl
.L3:
	add	QWORD [rbp-8], 1
.L2:
	mov	rax, QWORD [rbp-8]
	movzx	eax, BYTE [rax]
	test	al, al
	jne	.L4
	pop	rbp
	ret

