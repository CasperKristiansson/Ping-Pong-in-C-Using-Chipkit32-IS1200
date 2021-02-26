  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
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
.global delay
delay:

delayloop:    
    beqz    $a0, delaydone    # done if 0
    sub    $a0, $a0, 1    # decrement counter
    
    addi    $t0, $0, 4711    # for loop that takes 1 ms

delaymsloop:
    beqz    $t0, delayloop    # done if counter in loop finished
    sub    $t0, $t0, 1
    nop
    j    delaymsloop    # while $t0 > 0
    nop
    
delaydone:    
    jr     $ra  
    nop

.global time2string
	time2string:
	PUSH $ra
	
	#Add null-byte to the end of $a0
	la $t5, 0x00
	sb $t5, 5($a0)
	
	#First iteration store last digit in adress 5($a0)
	PUSH $a0
	la $a0, ($a1)
	jal hexasc
	nop
	POP $a0
	sb $v0, 4($a0)
	 
	
	#Second iteration store second to last digit in adress 4($a0)
	PUSH $a0
	srl $a1, $a1, 4
	la $a0, ($a1)
	jal hexasc
	nop
	POP $a0
	sb $v0, 3($a0)
	
	#Add ':' to middle
	la $t5, 0x3a
	sb $t5, 2($a0)
	
	#Fourth iteration store Second digit in adress 1($a0)
	PUSH $a0
	srl $a1, $a1, 4
	la $a0, ($a1)
	jal hexasc
	nop
	POP $a0
	sb $v0, 1($a0)
	
	#Fifth iteration store first digit in adress 0($a0)
	PUSH $a0
	srl $a1, $a1, 4
	la $a0, ($a1)
	jal hexasc
	nop
	POP $a0
	
	sb $v0, 0($a0)
	
	POP $ra
	jr $ra
	nop

.global enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop
