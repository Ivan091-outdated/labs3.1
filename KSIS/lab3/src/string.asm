STDIN equ 0
STDOUT equ 1
STDERR equ 2

SYS_READ equ 0
SYS_WRITE equ 1
SYS_EXIT equ 60

NEW_LINE equ 10
ZERO equ 0
ASCII_ZERO equ '0'
ASCII_NINE equ '9'

ASCII_A equ 'a'
ASCII_Z equ 'z'

LINE_SIZE equ 128
DIGIT_SIZE equ 128
POS_SIZE equ 8

section .data
	prompt db "Enter a line: ", ZERO
	lineMarker db "You have entered: ", ZERO
	newLine db NEW_LINE, ZERO
	digitsSumMarker db "Sum of digits in this line: ", ZERO
	charactersCountMarker db "Number of characters in this line: ", ZERO
	positiveMarker db "Running positive condition process...", ZERO
	negativeMarker db "Running negative condition process...", ZERO
	resultMarker db "Result: ", ZERO

section .bss
	line resb LINE_SIZE
	digit resb DIGIT_SIZE
	digitPos resb POS_SIZE

section .text
	global _start

%macro exit 0
	mov rax, SYS_EXIT
	mov rdi, ZERO
	syscall
%endmacro

_start:
	mov rax, prompt
	call _print

	call _getLine

	mov rax, lineMarker
	call _print
	
	mov rax, line
	call _print

	mov rax, newLine
	call _print

	mov rax, digitsSumMarker
	call _print

	mov rax, line
	call _digitsSumCount
	mov r8, rax
	call _printRAX

	mov rax, charactersCountMarker
	call _print

	mov rax, line
	call _charactersCount
	
	cmp rax, r8
	je _positiveCondition

	jmp _negativeCondition

_positiveCondition:
	call _printRAX
	mov rax, positiveMarker
	call _print

	mov rax, line
	call _positiveConditionProcess
	jmp _end

_negativeCondition:
	call _printRAX
	mov rax, negativeMarker
	call _print

	mov rax, line
	call _negativeConditionProcess
	jmp _end

_end:
	mov rax, newLine
	call _print

	mov rax, newLine
	call _print

	mov rax, resultMarker
	call _print

	mov rax, line
	call _print

	mov rax, newLine
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

_digitsSumCount:
	mov rbx, rax
	mov rax, ZERO

_digitsSumCountLoop:
	mov rcx, ZERO
	mov cl, [rbx]

	cmp cl, ZERO
	je _digitsSumCountExit

	cmp cl, NEW_LINE
	je _digitsSumCountExit

	inc rbx

	cmp cl, ASCII_ZERO
	jl _digitsSumCountLoop

	cmp cl, ASCII_NINE
	jg _digitsSumCountLoop

	add rax, rcx
	sub rax, ASCII_ZERO

	jmp _digitsSumCountLoop

_digitsSumCountExit:
	ret

_printRAX:
	mov rcx, digit
	mov rbx, NEW_LINE
	mov [rcx], rbx
	inc rcx
	mov [digitPos], rcx

_printRAXMakingLoop:
	mov rdx, ZERO
	mov rbx, 10
	div rbx
	push rax
	add rdx, ASCII_ZERO

	mov rcx, [digitPos]
	mov [rcx], dl
	inc rcx
	mov [digitPos], rcx

	pop rax
	cmp rax, ZERO	
	jne _printRAXMakingLoop

_printRAXPrintingLoop:
	mov rcx, [digitPos]
	
	mov rax, SYS_WRITE
	mov rdi, STDOUT
	mov rsi, rcx
	mov rdx, 1
	syscall	

	mov rcx, [digitPos]
	dec rcx
	mov [digitPos], rcx

	cmp rcx, digit
	jge _printRAXPrintingLoop

	ret

_charactersCount:
	mov rbx, rax
	mov rax, ZERO

_charactersCountLoop:
	mov rcx, ZERO
	mov cl, [rbx]

	cmp cl, ZERO
	je _charactersCountExit

	cmp cl, NEW_LINE
	je _charactersCountExit

	inc rbx

	cmp cl, ASCII_A
	jl _charactersCountLoop

	cmp cl, ASCII_Z
	jg _charactersCountLoop

	jmp _characterCountRAXIncrement

_characterCountRAXIncrement:
	inc rax
	jmp _charactersCountLoop

_charactersCountExit:
	ret

_positiveConditionProcess:
	mov rbx, ZERO
	mov bl, [rax]

	cmp bl, ZERO
	je _positiveExit

	cmp bl, NEW_LINE
	je _positiveExit

	cmp bl, ASCII_ZERO
	jle _positiveRAXIncrement

	cmp bl, ASCII_NINE
	jg _positiveRAXIncrement

	sub bl, 1
	sub bl, ASCII_ZERO
	add bl, ASCII_A
	mov [rax], bl

	jmp _positiveRAXIncrement

_positiveRAXIncrement:
	inc rax
	jmp _positiveConditionProcess

_positiveExit:
	ret

_negativeConditionProcess:
	mov rbx, ZERO
	mov bl, [rax]

	cmp bl, ZERO
	je _negativeExit

	cmp bl, NEW_LINE
	je _negativeExit

	inc rax
	mov bl, [rax]

	cmp bl, ZERO
	je _negativeExit

	cmp bl, NEW_LINE
	je _negativeExit

	push rax
	call _moveStringToTheLeft
	pop rax

	jmp _negativeConditionProcess

_negativeExit:
	ret

_moveStringToTheLeft:
	mov rbx, ZERO
	push rax

	inc rax
	mov bl, [rax]

	pop rax
	mov [rax], bl

	inc rax

	cmp bl, ZERO
	je _moveStringToTheLeftExit

	cmp bl, NEW_LINE
	je _moveStringToTheLeftExit

	jmp _moveStringToTheLeft

_moveStringToTheLeftExit:
	mov bl, ZERO
	mov [rax], rbx
	ret
