STDIN equ 0
STDOUT equ 1
STDERR equ 2

SYS_READ equ 0
SYS_WRITE equ 1
SYS_EXIT equ 60

ZERO equ 0
NEW_LINE equ 10
REPLACE equ '$'

SPACE equ ' '
LINE_SIZE equ 128
PREFIX_SIZE equ 2

section .data
	linePrompt db "Enter a line: ", ZERO
	prefixPrompt db "Enter a letter to replace: ", ZERO
	resultMarker db "Result: ", ZERO

section .bss
	line resb LINE_SIZE
	prefix resb PREFIX_SIZE

section .text
	global _start

%macro process 2
	mov rax, %1
	mov rbx, %2
	mov rcx, ZERO
	mov rdx, ZERO

	mov dl, [rbx]
	mov cl, [rax]

	cmp cl, NEW_LINE
	je _processEnd

	cmp cl, ZERO
	je _processEnd

	cmp cl, dl
	je _processReplace

	inc rax

_processLoop:
	mov cl, [rax]

	cmp cl, NEW_LINE
	je _processEnd

	cmp cl, ZERO
	je _processEnd

	cmp cl, SPACE
	jne _processIncrement

	inc rax
	mov cl, [rax]

	cmp cl, NEW_LINE
	je _processEnd

	cmp cl, ZERO
	je _processEnd

	cmp cl, dl
	je _processReplace

_processIncrement:
	inc rax
	jmp _processLoop

_processReplace:
	mov cl, REPLACE
	mov [rax], cl
	jmp _processIncrement

_processEnd:
%endmacro

%macro exit 0
	mov rax, SYS_EXIT
	mov rdi, ZERO
	syscall
%endmacro

_start:
	mov rax, linePrompt
	call _print
	call _getLine

	mov rax, prefixPrompt
	call _print
	call _getPrefix

	process line, prefix

	mov rax, resultMarker
	call _print

	mov rax, line
	call _print

	exit

_print:
	push rax
	mov rbx, ZERO

_printLoop:
	mov cl, [rax]

	cmp cl, ZERO
	je _printExit

	inc rax
	inc rbx
	jmp _printLoop

_printExit:
	mov rax, SYS_WRITE
	mov rdi, STDOUT
	pop rsi
	mov rdx, rbx
	syscall
	ret

_getLine:
	mov rax, SYS_READ
	mov rdi, STDIN
	mov rsi, line
	mov rdx, LINE_SIZE
	syscall
	ret

_getPrefix:
	mov rax, SYS_READ
	mov rdi, STDIN
	mov rsi, prefix
	mov rdx, PREFIX_SIZE
	syscall
	ret
