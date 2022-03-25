	.file	"combine.c"
	.intel_syntax noprefix
	.text
	.globl	printInfix
	.def	printInfix;	.scl	2;	.type	32;	.endef
printInfix:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	QWORD PTR 16[rbp], rcx
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 8[rax]
	test	rax, rax
	je	.L2
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 8[rax]
	mov	rcx, rax
	call	printInfix
.L2:
	mov	rax, QWORD PTR 16[rbp]
	movzx	eax, BYTE PTR [rax]
	movsx	eax, al
	mov	ecx, eax
	call	putchar
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 16[rax]
	test	rax, rax
	je	.L7
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 16[rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 124
	je	.L4
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 16[rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 38
	jne	.L5
.L4:
	mov	ecx, 40
	call	putchar
.L5:
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 16[rax]
	mov	rcx, rax
	call	printInfix
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 16[rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 124
	je	.L6
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 16[rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 38
	jne	.L7
.L6:
	mov	ecx, 41
	call	putchar
.L7:
	nop
	leave
	ret
	.globl	constructTree
	.def	constructTree;	.scl	2;	.type	32;	.endef
constructTree:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	QWORD PTR 16[rbp], rcx
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	test	rax, rax
	jne	.L13
	mov	ecx, 24
	call	malloc
	mov	rdx, rax
	mov	rax, QWORD PTR 16[rbp]
	mov	QWORD PTR [rax], rdx
	call	getchar
	mov	BYTE PTR -1[rbp], al
	mov	rax, QWORD PTR 16[rbp]
	mov	rdx, QWORD PTR [rax]
	movzx	eax, BYTE PTR -1[rbp]
	mov	BYTE PTR [rdx], al
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR 16[rax], 0
	mov	rdx, QWORD PTR 16[rbp]
	mov	rdx, QWORD PTR [rdx]
	mov	rax, QWORD PTR 16[rax]
	mov	QWORD PTR 8[rdx], rax
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	mov	rax, QWORD PTR 8[rax]
	test	rax, rax
	jne	.L10
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 38
	je	.L11
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 124
	jne	.L10
.L11:
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	add	rax, 8
	mov	rcx, rax
	call	constructTree
.L10:
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	mov	rax, QWORD PTR 16[rax]
	test	rax, rax
	jne	.L13
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 38
	je	.L12
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	movzx	eax, BYTE PTR [rax]
	cmp	al, 124
	jne	.L13
.L12:
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR [rax]
	add	rax, 16
	mov	rcx, rax
	call	constructTree
.L13:
	nop
	leave
	ret
	.globl	freeTree
	.def	freeTree;	.scl	2;	.type	32;	.endef
freeTree:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	QWORD PTR 16[rbp], rcx
	cmp	QWORD PTR 16[rbp], 0
	je	.L16
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 8[rax]
	mov	rcx, rax
	call	freeTree
	mov	rax, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 16[rax]
	mov	rcx, rax
	call	freeTree
	mov	rcx, QWORD PTR 16[rbp]
	call	free
.L16:
	nop
	leave
	ret
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "%d\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	call	__main
	lea	rax, -4[rbp]
	mov	rdx, rax
	lea	rcx, .LC0[rip]
	call	scanf
	jmp	.L18
.L19:
	call	getchar
	mov	QWORD PTR -16[rbp], 0
	lea	rax, -16[rbp]
	mov	rcx, rax
	call	constructTree
	mov	rax, QWORD PTR -16[rbp]
	mov	rcx, rax
	call	printInfix
	mov	ecx, 10
	call	putchar
	mov	rax, QWORD PTR -16[rbp]
	mov	rcx, rax
	call	freeTree
	mov	eax, DWORD PTR -4[rbp]
	sub	eax, 1
	mov	DWORD PTR -4[rbp], eax
.L18:
	mov	eax, DWORD PTR -4[rbp]
	test	eax, eax
	jg	.L19
	mov	eax, 0
	leave
	ret
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putchar;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	getchar;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.def	scanf;	.scl	2;	.type	32;	.endef
