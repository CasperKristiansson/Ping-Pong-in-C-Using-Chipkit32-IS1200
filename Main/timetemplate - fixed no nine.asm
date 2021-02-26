  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5950
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
 hexasc:
 	add $t5, $zero, $zero
	li $t5, 0x0f 
	and $a0, $t5, $a0
	la $v0, ($a0)
	
	slti $t6, $a0, 10
	beq $t6, 1, number
	nop
	beq $t6, 0, letter
	nop
	
number:	
	addi $v0, $v0, 0x30 
	jr $ra
	nop
letter:
	addi $v0, $v0, 0x37
	jr $ra
	nop
  #
delay:
	la $t1, ($a0) 		#Loading $t1 with the parameter decided when calling
whileloop:
	slt $t2, $zero, $t1 #If 0 < $t1, give $t2 value 1, else give $t2 value 0
	beq $t2, 0, done #If $t2 has the value 0 => (0 >= $t1), then jump to done
	nop
	addi $t1, $t1, -1 #Subtract -1 from $t1
	add $t3, $t3, $zero #Initialize $t3 by setting it's value to 0
	addi $t4, $t4, 10  #Give $t4 the value 4711
	beq $t2, 1, forloop  #If $t2 has the value 1 => (0 < $t1), then jump to forloop
	nop
	
forloop:
	slt $t5, $t3, $t4  	#If $t3 < $t4, give $t5 value 1, else give $t5 value 0 
	beq $t5, 0, whileloop #If $t5 has value 0 => ($t3 >= $t4), then jump to whileloop
	nop
	addi $t3, $t3, 1 #Add 1 to $t3
	j forloop #Jump to forloop
	nop
done:
	jr $ra
	nop

time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	la $s1, ($a1)
	la $s0, ($a0)	

	#Add null-byte to the end of $a0
	la $t5, 0x00
	sb $t5, 5($s0)
	
	#First iteration store last digit in adress 5($a0)
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 4($s0)
	 
	#Second iteration store second to last digit in adress 4($a0)

	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 3($s0)
	
	#Add ':' to middle
	la $t5, 0x3a
	sb $t5, 2($s0)
	
	#Fourth iteration store Second digit in adress 1($a0)
	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 1($s0)
	
	#Fifth iteration store first digit in adress 0($a0)
	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	
	#For 'DING'
	sb $v0, 0($s0)
	li $t7, 0x30
	lb $t9, 0($s0)
	bne $t7, $t9, klar
	nop
	
	lb $t9, 1($s0)
	bne $t7, $t9, klar
	nop
	
	lb $t9, 3($s0)
	bne $t7, $t9, klar
	nop

	lb $t9, 4($s0)
	bne $t7, $t9, klar
	nop

	# 0x44 'D' 0x49 'I' 0x4e 'N' 0x47 'G'
	li $t8, 0x474e4944 # 'G' 'N' 'I' 'D'
	sw $t8, 0($s0) #store ding in 
	la $t5, 0x00
	sb $t5, 4($s0)
	
	# End of for 'DING'

klar:
	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop

	
