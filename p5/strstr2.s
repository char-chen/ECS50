	.file	"strstr2.c"
	.intel_syntax noprefix
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
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	and	esp, -16
	sub	esp, 96
	mov	DWORD PTR [esp+54], 1886348624
	mov	DWORD PTR [esp+58], 1914725740
	mov	DWORD PTR [esp+62], 1869640549
	mov	DWORD PTR [esp+66], 1948279918
	mov	DWORD PTR [esp+70], 1701847151
	mov	DWORD PTR [esp+74], 1701605487
	mov	DWORD PTR [esp+78], 1869117216
	mov	DWORD PTR [esp+82], 1936028192
	mov	DWORD PTR [esp+86], 1684959088
	mov	WORD PTR [esp+90], 46
	mov	WORD PTR [esp+51], 25936
	mov	BYTE PTR [esp+53], 0
	mov	DWORD PTR [esp+46], 1868918816
	mov	BYTE PTR [esp+50], 0
	mov	DWORD PTR [esp+28], 1886610802
	mov	DWORD PTR [esp+32], 543452783
	mov	DWORD PTR [esp+36], 1344302964
	mov	DWORD PTR [esp+40], 1819307877
	mov	WORD PTR [esp+44], 101
	mov	BYTE PTR [esp+27], 0
	lea	eax, [esp+51]
	mov	DWORD PTR [esp+4], eax
	lea	eax, [esp+54]
	mov	DWORD PTR [esp], eax
	call	mystrstr
	mov	DWORD PTR [esp+92], eax
	mov	eax, DWORD PTR [esp+92]
	mov	DWORD PTR [esp], eax
	call	puts
	lea	eax, [esp+46]
	mov	DWORD PTR [esp+4], eax
	lea	eax, [esp+54]
	mov	DWORD PTR [esp], eax
	call	mystrstr
	mov	DWORD PTR [esp+92], eax
	mov	eax, DWORD PTR [esp+92]
	mov	DWORD PTR [esp], eax
	call	puts
	lea	eax, [esp+28]
	mov	DWORD PTR [esp+4], eax
	lea	eax, [esp+54]
	mov	DWORD PTR [esp], eax
	call	mystrstr
	mov	DWORD PTR [esp+92], eax
	cmp	DWORD PTR [esp+92], 0
	jne	.L2
	mov	DWORD PTR [esp], OFFSET FLAT:.LC0
	call	puts
	jmp	.L3
.L2:
	mov	DWORD PTR [esp], OFFSET FLAT:.LC1
	call	puts
.L3:
	lea	eax, [esp+27]
	mov	DWORD PTR [esp+4], eax
	lea	eax, [esp+54]
	mov	DWORD PTR [esp], eax
	call	mystrstr
	mov	DWORD PTR [esp+92], eax
	mov	eax, DWORD PTR [esp+92]
	mov	DWORD PTR [esp], eax
	call	puts
	mov	eax, 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	mystrstr
	.type	mystrstr, @function
mystrstr:
.LFB1:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
#APP
# 31 "strstr2.c" 1
	.intel_syntax noprefix

# 0 "" 2
# 32 "strstr2.c" 1
	mov edi, [ebp+8] 
mov esi, [ebp+12] 
mov ecx, 0
mov al, [esi]
cmp al, 0
je  done
loop:
mov ah, [edi]
cmp ah, 0
je  done2
mov al, [esi]
cmp al, ah
jne increment
mov ecx, 1
loop2:
mov al, [esi + ecx]
cmp al, 0
je  done
mov ah, [edi+ecx]
cmp ah, al
jne increment
inc ecx
jmp loop2
increment:
inc edi
jmp loop
done2:
mov eax, 0
leave
ret
done: 
mov eax, edi
leave
ret

# 0 "" 2
#NO_APP
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	mystrstr, .-mystrstr
	.ident	"GCC: (GNU) 4.8.3 20140911 (Red Hat 4.8.3-7)"
	.section	.note.GNU-stack,"",@progbits
