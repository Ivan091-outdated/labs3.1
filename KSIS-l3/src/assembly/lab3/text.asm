section .data
text db "1Some text2", '\0'

section .text
global _start

_start:
	push text
	call strlen
	add rsp, 8

	push rax
	push text 
	call checkCondition

	cmp rax, 1
	je .first
.second:
	call reverseText
	jmp .done
.first:
	call replaceByCode
.done:
	sub rsp, 16
	
	mov rax, 0x3c
	mov rdi, 0x0
	syscall

;long checkCondition (char* string, long len)
;1 - first condition
;2 - second
checkCondition:
	push rbp
	mov rbp, rsp
	mov rsi, [rbp + 16]
	mov rax, [rbp + 24]
	
	mov bl, [rsi]		;first symbol in text.	
	mov dl, [rsi + rax]
	
	mov cl, dl
	call .isNum
	cmp rax, 0
	je .second

	mov cl, bl
	call .isNum
	cmp rax, 0
	je .second

	cmp dl, bl
	jne .second		

.first:
	mov rax, 1
	jmp .done	

.second:	
	mov rax, 2

.done:
	mov rsp, rbp
	pop rbp
	ret

;.isNum(char cl)
.isNum:
	mov rax, 1
	cmp cl, '0'
	jl .notNum
	cmp cl, '9'
	jg .notNum
	ret
.notNum:
	mov rax, 0
	ret

;reverseText(char* text)
reverseText:
	push rbp
	mov rbp, rsp
	xor rax, rax
	
	mov rsi, [rbp + 16]
.nextChar:
	cmp [rsi], byte '\0'
	je .reverce
	lodsb
	push rax
	jmp .nextChar
.reverce:
	mov rsi, [rbp + 16]	
.nextRevercedChar:
	cmp [rsi], byte '\0'
	je .done
	pop qword [rsi]
	inc rsi
	jmp .nextRevercedChar
		
.done:
	mov rsp, rbp
	pop rbp
	ret
		

;replaceByCode(char* text)
replaceByCode:
	push rbp
	mov rbp, rsp
	mov rsi, [rbp + 16]
.loop:
	lodsb 
	cmp al, '\0'
	je .done	
	
	mov dl, 10
	div dl
	mov [rsi], dl
	jmp .loop	
.done:
	mov rsp, rbp
	pop rbp
	ret

;--------------------------------------------------
; long strlen(char* buffer)
strlen:
	push rbp
	mov rbp, rsp
	xor rax, rax			; rax <- 0
	movzx esi, byte [rbp + 15]	; esi <- first byte before buffer
.loop:					; finds index of '\0' in buffer
	inc esi				; goto next symbol
	inc rax				
	test esi, esi			
	je .loop			; while esi != 0

	pop rbp
	ret

