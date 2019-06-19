#############################################################
#															#
#		Name: Colton Piper									#
#		Class: Computer Organization 1						#
#		Assignment: Assignment 5 is to determine  the sum, 	#
#	min, max, mean and var of a list of numbers.			#
#															#
#############################################################


		.data
descr:		.asciiz	"Enter in integer values, one per line, terminated by a negative value. \n"
sum:		.asciiz "Sum: "			# Register $s4
min:		.asciiz "Min: "			# Register $s2
max: 		.asciiz	"Max: "			# Register $s3
mean:		.asciiz "Mean: "		# FP Register $f0,	Counter is in $f1/$s1
var:		.asciiz	"Variance: "	# FP Register $f2,	Counter is in $f1/$s1
newLine:	.asciiz "\n"
ask:		.asciiz "Enter in some integers: "
end:		.asciiz "Program has ended"
array:		.word	0:100				# Allocates 100 words, assign zeros 
		.align 2
		.text
		.globl main

main:
		la $s0, array		# This saves the address of the array to register s0, goes by 4s per word
		li $s1, 0			# This will be the counter of the array
		li $s2, 0
		li $s3, 0
		li $s4, 0
		li $s5, 0

		# Prints out starting message
		li $v0, 4
		la $a0, descr
		syscall
		li $v0, 4
		la $a0, ask
		syscall

		# Enter in the first integer and moves it to a temp register
		li $v0, 5
		syscall
		move $t0, $v0

		# This puts zero into the temporary register t1
		li $t1, 0

		# This puts number into max and min as it is both
		move $s2, $t0
		move $s3, $t0

		# Checks to see if the integer is positive head to the loop t1 = 0  <  number = t0
		blt $t1, $t0, enterNums

		# Prints program has ended
		li $v0, 4
		la $a0, end
		syscall

		# Ends the program if it is a negative
		li $v0, 10
		syscall




######################################################################################################
######################################################################################################
	



enterNums:	
		# This jumps to the subroutine to check if the integer is bigger or smaller than the max
		blt $t0, $s2, setMin
		blt $s3, $t0, setMax

		# This adds to the sum for each number
		addu $s4, $s4, $t0

		# This stores the word
		sw $t0, 0($s0)

		# Now increment the counter and address of array
		addiu $s0, $s0, 4
		addiu $s1, $s1, 1

		# Enter in the next integer and moves it to a temp register
		li $v0, 5
		syscall
		move $t0, $v0


		# Checks to see if the integer is negative
		blt $t1, $t0, enterNums

		# This prints out the sum
		li $v0, 4
		la $a0, sum
		syscall
		li $v0, 1
		move $a0, $s4
		syscall
		li $v0, 4
		la $a0, newLine
		syscall

		# This prints out the min and max
		li $v0, 4
		la $a0, min
		syscall
		li $v0, 1
		move $a0, $s2
		syscall
		li $v0, 4
		la $a0, newLine
		syscall
		li $v0, 4
		la $a0, max
		syscall
		li $v0, 1
		move $a0, $s3
		syscall
		li $v0, 4
		la $a0, newLine
		syscall

		# This then computes the mean by first converting the sum into a floating point 
		#      	register then dividing by the counter
		mtc1 $s4, $f0
		cvt.s.w $f0, $f0
		mtc1 $s1, $f1
		cvt.s.w $f1, $f1
		div.s $f0, $f0, $f1  	# mean = mean / counter
		li $v0, 4
		la $a0, mean
		syscall
		li $v0, 2
		mov.s $f12, $f0
		syscall
		li $v0, 4
		la $a0, newLine
		syscall

		# This computes the variance
		# First we go into another loop as we will need to traverse the array
		# This will be new counter we will use and compare with s1 as we no longer need minimum
		# Also let us reset the address to the beggining of the array
		li $s2, 0 
		la $s0, array




######################################################################################################
######################################################################################################




# Recall That the mean = $f0 and variance = $f2,
# Also that original counter = $s1, address = $s0, and new counter = $s2
varCalc:
		# This loads the word from the array
		lw $s3, 0($s0)
		mtc1 $s3, $f3
		cvt.s.w $f3, $f3

		# This increments the address for next load and adds to new counter 
		addiu $s0, $s0, 4
		addiu $s2, $s2, 1

		# This does the math for the iteration in a temporary FP register $f4 
		sub.s $f4, $f3, $f0		# number - mean
		mul.s $f4, $f4, $f4		# squaring the number
		add.s $f2, $f2, $f4		# var = var + (next number of summation)

		# This then does the loop if we have not reached the number of positive integers entered
		blt $s2, $s1, varCalc

		# This does the last division for the variance 
		mtc1 $s2, $f1
		cvt.s.w $f1, $f1

		div.s $f2, $f2, $f1 	# var = var / counter

		# This then prints out the variance
		li $v0, 4
		la $a0, var
		syscall
		li $v0, 2
		mov.s $f12, $f2
		syscall
		li $v0, 4
		la $a0, newLine
		syscall

		# Ends the program if it is a negative
		li $v0, 10
		syscall




######################################################################################################
######################################################################################################




setMin:
		move $s2, $t0
		j enterNums

setMax:	
		move $s3, $t0
		j enterNums


