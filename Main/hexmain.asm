  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,17	# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
hexasc:
	add $t0, $zero, $zero
	li $t0, 0x0f 
	and $a0, $t0, $a0
	la $v0, ($a0)
	
	slti $t1, $a0, 10
	beq $t1, 1, number
	beq $t1, 0, letter
	
number:	
	addi $v0, $v0, 0x30 
	jr $ra
letter:
	addi $v0, $v0, 0x37
	jr $ra
  #

