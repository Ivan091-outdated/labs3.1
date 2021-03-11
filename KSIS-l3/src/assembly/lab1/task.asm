section .bss
buffer resb 30

section .data new_line db 0xa surname	db "Ivan Karnasevich", 0	;just my name surname_len

section .text
global _start 

_start:
	push qword 10
	push buffer
	call read			; reads value from keyboard
	
	push rax
	call atoi			; parse the value to long

	cmp rax, [surname_len]
	jl .rax				; if rax < *surname_len
	jmp .len			; 	jmp .rax
					; else
.rax:					;	jmp .len
	push rax
	jmp .print			; pushs rax as argument of println()

.len:
	push qword [surname_len]	; pushs *surname_len as argument of printline()
	jmp .print

.print:	
	push surname
	call println
	
	mov rax, 0x3c
	mov rdi, 0x0
	syscall

;--------------------------------------------------
; int atoi(string* str_to_parse)
atoi:
	push rbp
	mov rbp, rsp
	mov rdi, [rbp + 16] 
	xor rax, rax            ; Set initial total to 0
     
.convert:
	movzx rsi, byte [rdi]   ; Get the current character
	test rsi, rsi	        ; Check for \0
	je .done
    
	cmp rsi, 48             ; Anything less than 0 is invalid
	jl .error
    
	cmp rsi, 57             ; Anything greater than 9 is invalid
	jg .error
     
	sub rsi, 48             ; Convert from ASCII to decimal 
	imul rax, 10            ; Multiply total by 10
	add rax, rsi            ; Add current digit to total
    
	inc rdi                 ; Get the address of the next character
	jmp .convert

.error:
	mov rax, -1             ; Return -1 on error

.done:
	pop rbp
    	ret 8                   ; Return total or error code
;--------------------------------------------------
; void print(char* str, int len)
print:
	push rbp
	mov rbp, rsp

	mov rax, 0x1			; set sysfunction write()
	mov rdi, 0x1 			; set output stdout
	mov rsi, [rbp + 16]		; rcx <- str
	mov rdx, [rbp + 24]		; rdx <- len					
	syscall

	pop rbp
	ret 16

;--------------------------------------------------
; void println(char* str, int len)
println:
	push rbp
	mov rbp, rsp

	push qword [rbp + 24]		
	push qword [rbp + 16]
	call print			; call print function to print data
	
	mov rax, 0x1			; set sysfunction write()
	mov rdi, 0x1			; set output stdout
	mov rsi, new_line	        ; "\n" -> rcx
	mov rdx, 0x1			; 1 -> rdx as size of "\n"
	syscall
	
	pop rbp
	ret 16
;--------------------------------------------------
; char* read(char* buffer, long size)
read:
	push rbp
	mov rbp, rsp
	
	xor rax, rax			; set sysfunction read()
	xor rdi, rdi			; set stdin as input
	mov rsi, [rbp + 16]		; set a  buffet to write in
	mov rdx, [rbp + 24]		; set size of the buffer
	syscall
	
	mov rcx, rdx			; rcx <- total size of buffer			
.loop1:					; finds last '\n' 
	cmp [rsi + rcx], byte 0xa	; 
	je .done			; if rsi[rcx] == '\n' break
	loop .loop1			; while true
.done:
	mov [rsi + rcx], byte 0		; replaces the "\n" by "\0"
	mov rax, rsi			; moves result to rax

	pop rbp
	ret 16

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
	ret 8
