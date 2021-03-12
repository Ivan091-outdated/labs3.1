section .data
text byte "1Some text2", '\0'

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
.first:
reverse text 	cmp [esi], '\0'
	je .reverce
.second:

;long checkCondition (char* string, long len)
;1 - first condition
;2 - second
checkCondition:
	push rbp
	mov rbp, rsp
	mov rsi, [rbp + 16]
	mov rax, [rbp + 24]
	
	push byte [rsi]		;first symbol in text.	
	
	mov dl, [rsi + rax]
	pop bl
	
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
	jmp, .done	

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
	
	mov rsi, [rbp + 16]
.nextChar:
	cmp [rsi], '\0'
	je .reverce
	lodsb
	push al
	jmp .nextChar
.reverce:
	mov rsi, [rbp + 16]	
.nextRevercedChar:

	cmp [rsi], '\0'
	je .done
	pop [rsi]
	inc rsi
	jmp .nextRevercedChar
		
.done:
	mov rsp, rbp
	pop rbp
	ret
		

;replaceByCode(char* text)
reblaceByCode:
	push rbp
	mov rbp, rsp
	mov rsi, [rbp + 16]
.loop:
	lodsb 
	cmp al, '\0'
	je .done	
	
	div byte 10
	mov [rsi], dl
	jmp .loop	
.done:
	mov rsp, rbp
	pop rbp
	ret
