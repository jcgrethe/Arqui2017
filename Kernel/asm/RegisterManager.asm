GLOBAL outIO
GLOBAL inIO

outIO:
	push rbp
	mov rbp, rsp

	mov rdx, rdi
	mov rax, rsi

	out dx, al

	leave
	ret

inIO:
	push rbp
	mov rbp, rsp

	mov rdx, rdi

	in al, dx

	leave
	ret