GLOBAL outIO
GLOBAL inIO

outIO:
	push rbp
	mov rbp, rsp
	push rdx
	mov rdx, rdi
	mov rax, rsi

	out dx, al
	pop rdx
	leave
	ret

inIO:
	push rbp
	mov rbp, rsp
	push rdx
	xor rax,rax
	mov rdx, rdi

	in al, dx
	pop rdx
	leave
	ret