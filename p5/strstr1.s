	.file	"strstr1.c"
	.section	.rodata
.LC0:
	.string	"OK"
.LC1:
	.string	"Not OK"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$96, %esp
	movl	$1886348624, 54(%esp)
	movl	$1914725740, 58(%esp)
	movl	$1869640549, 62(%esp)
	movl	$1948279918, 66(%esp)
	movl	$1701847151, 70(%esp)
	movl	$1701605487, 74(%esp)
	movl	$1869117216, 78(%esp)
	movl	$1936028192, 82(%esp)
	movl	$1684959088, 86(%esp)
	movw	$46, 90(%esp)
	movw	$25936, 51(%esp)
	movb	$0, 53(%esp)
	movl	$1868918816, 46(%esp)
	movb	$0, 50(%esp)
	movl	$1886610802, 28(%esp)
	movl	$543452783, 32(%esp)
	movl	$1344302964, 36(%esp)
	movl	$1819307877, 40(%esp)
	movw	$101, 44(%esp)
	movb	$0, 27(%esp)
	leal	51(%esp), %eax
	movl	%eax, 4(%esp)
	leal	54(%esp), %eax
	movl	%eax, (%esp)
	call	mystrstr
	movl	%eax, 92(%esp)
	movl	92(%esp), %eax
	movl	%eax, (%esp)
	call	puts
	leal	46(%esp), %eax
	movl	%eax, 4(%esp)
	leal	54(%esp), %eax
	movl	%eax, (%esp)
	call	mystrstr
	movl	%eax, 92(%esp)
	movl	92(%esp), %eax
	movl	%eax, (%esp)
	call	puts
	leal	28(%esp), %eax
	movl	%eax, 4(%esp)
	leal	54(%esp), %eax
	movl	%eax, (%esp)
	call	mystrstr
	movl	%eax, 92(%esp)
	cmpl	$0, 92(%esp)
	jne	.L2
	movl	$.LC0, (%esp)
	call	puts
	jmp	.L3
.L2:
	movl	$.LC1, (%esp)
	call	puts
.L3:
	leal	27(%esp), %eax
	movl	%eax, 4(%esp)
	leal	54(%esp), %eax
	movl	%eax, (%esp)
	call	mystrstr
	movl	%eax, 92(%esp)
	movl	92(%esp), %eax
	movl	%eax, (%esp)
	call	puts
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	strstr
	.type	strstr, @function
strstr:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L6
	movl	8(%ebp), %eax
	jmp	.L7
.L6:
	jmp	.L8
.L14:
	movl	8(%ebp), %eax
	movzbl	(%eax), %edx
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	je	.L9
	jmp	.L10
.L9:
	movl	$1, -4(%ebp)
.L13:
	movl	-4(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L11
	movl	8(%ebp), %eax
	jmp	.L7
.L11:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %edx
	movl	-4(%ebp), %ecx
	movl	12(%ebp), %eax
	addl	%ecx, %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	je	.L12
	jmp	.L10
.L12:
	addl	$1, -4(%ebp)
	jmp	.L13
.L10:
	addl	$1, 8(%ebp)
.L8:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L14
	movl	$0, %eax
.L7:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	strstr, .-strstr
	.ident	"GCC: (GNU) 4.8.3 20140911 (Red Hat 4.8.3-7)"
	.section	.note.GNU-stack,"",@progbits
