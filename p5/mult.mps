.data	0xA00
arr:	.space	 10
	#.word 1
	#.word 7
	#.word 4
	#.word 3
	#.word 2
	#.word 5
	#.word 10
	#.word 3
	#.word 4
	#.word 4
.data	0xA30
arr2:	.space	 10	
	#.word 1
	#.word 7
	#.word 3
	#.word 3
	#.word 2
	#.word 5
	#.word 10
	#.word 3
	#.word 4
	#.word 4
	.text	0
main:
init:	add	$t4, $0, $0	
	addu	$t0, $0, $0
	la	$t3, arr
	la	$t6, arr2	
loop1:	sll	$t1, $t0, 2	
	add	$t1, $t1, $t6	
	lw	$a2, 0($t1)	
	nop
	sll	$t9, $t0, 2	
	add	$t9, $t9, $t3	
	lw	$a1, 0($t9)	
	nop
	jal	multiply
print:	add	$a0, $t4, $0	
	addi	$v0, $0, 1
	syscall
	subu	$t4, $t4, $t4	
	addiu	$t0, $t0, 1	
	slti	$t2, $t0, 10	
	bne	$t2, $0, loop1	
	nop
	addiu	$v0, $0, 10
	syscall
	.end

multiply:	
loop2:	beq	$a2, $0, return 	
	nop
	andi	$t8, $a2, 1	
	beq	$t8, $0, shift	
	nop
	add	$t4, $t4, $a1	
shift:	sll	$a1, $a1, 1
	sra	$a2, $a2, 1	
	j	loop2
	nop
return:	jr	$ra
