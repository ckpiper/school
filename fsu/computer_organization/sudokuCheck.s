#############################################################
#															#
#		Name: Colton Piper									#
#		Class: Computer Organization 1						#
#		Assignment: Assignment sudoku is to check if the 	#
#	sudoku puzzle given is a valid puzzle or invalid.		#
#															#
#############################################################

		.data
puzz:		.asciiz "/home/colton/work/gradSchool/year1/assembly/validPuzzle.txt"  # Valid Puzzle
puzz1:		.asciiz "/home/colton/work/gradSchool/year1/assembly/invalidPuzzle1.txt"  # Breaks rows/cols
puzz2:		.asciiz "/home/colton/work/gradSchool/year1/assembly/invalidPuzzleRow.txt"  # Breaks row rule
puzz3:		.asciiz "/home/colton/work/gradSchool/year1/assembly/invalidPuzzleCol.txt"  # Breaks column rule
puzz4:		.asciiz "/home/colton/work/gradSchool/year1/assembly/invalidPuzzleBlock.txt"  # Breaks block rule
file:		.asciiz "readFile.txt"
rowGood:	.asciiz "The rows are valid.\n"
colGood:	.asciiz	"The columns are valid.\n"
blockGood:	.asciiz	"The blocks are valid.\n"
val:		.asciiz "The puzzle is valid.\n"
missing:	.asciiz "The puzzle is invalid because its missing "
fromRow:	.asciiz	" from Row "
fromCol:	.asciiz	" from Col "
fromBlo:	.asciiz	" from Block "
period:		.asciiz ".\n"
newLine:	.asciiz "\n"
comma:		.asciiz ", "
numbers:	.space	1024
		.align 2
		.text
		.globl main


main:
		# Open a file for reading
		li $v0, 13			# system call for opening a file
		la $a0, puzz		# file name
		li $a1, 0			# File Flag, Open a file for reading (0), writing is (1)
		li $a2, 0			# permissions/mode is ignored
		syscall				# Open the file (file descriptor returned in $v0)
		move $s0, $v0		# Save the file descriptor 

		# Read from file
		li $v0, 14			# System call for reading a file
		move $a0, $s0		# Give the file descriptor to be read from
		la $a1, numbers		# The buffer (where the data is to be read into)
		li $a2, 1024			# The byte length of the buffer
		syscall				# Read the file

		# Close the file 
		li $v0, 16			# System call for closing a file
		move $a0, $s0		# Give fil descriptor to be closed
		syscall				# Close the file

		# Print out puzzle onto console
		la $s0, numbers 	# Give address of numbers to $s0
		la $t0, 0($s0)		# Give address to temp register plus a shift if you want
		move $a0, $t0		# Give address of string to be printed
		li $v0, 4			# System call to print out a string
		syscall

		li $s2, 0		# This starts out saying that the rows are valid, valid = 0

		# This function takes care of the rows if $s2 is not zero when the program comes back then invalid
		li $s1, 0 		# This is the initial counter for the row we are on
		li $a0, 18		# This is the amount needed to figure out start of each row
		li $a1, 2		# This holds the amount needed to move forward in a row
		jal line
		bne $s2, $zero, end
		li $v0, 4
		la $a0, rowGood
		syscall

		# This function takes care of the cols and if it comes back then they are valid
		li $s1, 0 		# This is the initial counter for the column we are on
		li $a0, 2		# This is the amount needed to figure out start of each column
		li $a1, 18		# This holds the amount needed to move forward in a column
		jal line
		bne $s2, $zero, end
		li $v0, 4
		la $a0, colGood
		syscall

		# This funtion takes care of the blocks and if it comes back then they are valid
		li $s1, 0 		# This is the initial counter for the block we are on
		jal block
		bne $s2, $zero, end
		li $v0, 4
		la $a0, blockGood
		syscall

		# If the program makes it to this point of the program then it is a valid puzzle
		li $v0, 4
		la $a0, val
		syscall

		# Close program
		li $v0, 10			# System call for exiting program
		syscall				# Exit Program



line:
		# We will save the address of numbers in a register as we will add to it
		la $s0, numbers			# This will hold the address for the array as it will reset each time we go through

		# This moves argument which is 18 or 2 in $a0 and $a1 into a temp registers
		move $t0, $a0		# This holds start multiplier
		move $t1, $a1		# This holds adder for moving in a row/column

		# This sets $s0 to the correct address where the row/col starts recall
		move $a0, $t0			# puts into argument register to be passed into start function
		addiu $sp, $sp, -12
		sw $ra, 8($sp)			# Preserves the return address to get back to main
		sw $t0, 4($sp)
		sw $t1, 0($sp)
		jal start
		move $t3, $v0			# Moves returned value (18 * (row # -1)) into temp register 
		lw $t1, 0($sp)
		lw $t0, 4($sp)
		lw $ra, 8($sp)
		addiu $sp, $sp, 12		# Restores stack pointer
		addu $s0, $s0, $t3  	# This completes the start = start + 18 * (row # - 1)

		# We will go to another function and we will send the address we are on 
		# 		If the number returned is not 0 then we know that the row failed.	
		li $s3, 49				# This is the counter for each digit from 1 to 9
		addiu $sp, $sp, -12
		sw $ra, 8($sp)			# Preserves the return address to get back to main
		sw $t0, 4($sp)
		sw $t1, 0($sp)
		move $a0, $t1			# This will put in adder for the row/column into digit
		jal digit
		lw $t1, 0($sp)
		lw $t0, 4($sp)
		lw $ra, 8($sp)
		addiu $sp, $sp, 12		# Restores stack Pointer

		# This restores $a0, $a1 if we need to loop around again as they will be moved back into $tx
		move $a0, $t0
		move $a1, $t1

		# This branches us to jump if we found the puzzle is invalid by $s2 not equal to zero
		bne $s2, $zero, jump

		# This will then loop back to the rows if $s1 is less than 9 
		addiu $s1, $s1, 1		# Iterate through the rows/cols
		li $t0, 9				# Our temp register to hold 9
		blt $s1, $t0, line		# This branches to rows/cols

		# $s1 goes from 0 to 8 for the row/col count and when it gets to 9 we will
		#			return to the main function and continue through that 
		jr $ra


digit:
		# Each time we search for a new element we need to start back at the beginning of the row
		#		which is stored in $s0, which we do not want to change. Thus we will set $s5 to
		# 		be $s0 here and then add to it as we go through the row/col in digFind function.
		move $s5, $s0
		move $t0, $a0		# This is the adder to move through row/col

		# Now we will go into another function that will loop through the row to find the digit we are on
		addiu $sp, $sp, -8
		sw $ra, 4($sp)		# This preserves the return address to return to the main
		sw $t0, 0($sp)
		li $s4, 0			# This will be the counter for each element check in the row
		move $a0, $t0		# This is the adder to move through row/col
		jal digFind
		lw $t0, 0($sp)
		lw $ra, 4($sp)
		addiu $sp, $sp, 8	# This restores the stack

		# This branches us to jump if we found the puzzle is invalid by $s2 not equal to zero
		bne $s2, $zero, jump

		# This branches into digit again if $s3 is les than 58
		addiu $s3, $s3, 1		# Iterate through the digits
		li $t1, 58				# Our temp register to hold 58
		move $a0, $t0			# Restores $a0 = $t0 as we copy $a0 into $t0 if we loop around again
		blt $s3, $t1, digit		# This branches to digit

		jr	$ra


digFind:
		# This is the adder to move through the row/col
		move $t1, $a0
		
		# This branch is to make sure we have gone over the amount of elements in the row
		li $t0, 9				# Our temp register to hold 9
		beq $s4, $t0, misCheck 	# If $s4 gets to 9 that means we haven't found the digit and thus it is not in the row
		addiu $s4, $s4, 1		# Iterate through the elements if we need to go through them all

		# This branch is to compare the digit with the element in check
		lbu $t0, 0($s5)				# This loads the element in the address stored in $s5
		addu $s5, $s5, $t1			# This moves the address to next element if needed when we loop around
		move $a0, $t1			# Restores $a0 as we need $t1 to be $a0 above if we loop around again
		subu $t0, $t0, $s3		# This subtracts the element from the digit
		bne $t0, $zero, digFind	# If the difference is zero than they are the same digit and we continue

		jr $ra


# This is to check if we missed while checking the rows or checking the columns
misCheck:
		li $t0, 18
		beq	$t0, $t1, misCol	# This brings us to misCol using the adder to move through row/col


misRow:
		# This is invalid because it is missing a digit in the row 
		li $v0, 4
		la $a0, missing
		syscall

		# This is temp for digit so we can subtract it to get non ascii value
		move $t0, $s3
		addiu $t0, $t0, -48
		li $v0, 1
		move $a0, $t0
		syscall

		li $v0, 4
		la $a0, fromRow
		syscall

		# This is temp for row add 1 to it 
		move $t0, $s1
		addiu $t0, $t0, 1
		li $v0, 1
		move $a0, $t0
		syscall

		li $v0, 4
		la $a0, period
		syscall

		# This puts a non zero number into $s2 which means that the puzzle is invalid 
		li $s2, 1

		# This then jumps back to digit loop
		jr $ra


misCol:
		# This is invalid because it is missing a digit in the column
		li $v0, 4
		la $a0, missing
		syscall

		# This is temp for digit so we can subtract it to get non ascii value
		move $t0, $s3
		addiu $t0, $t0, -48
		li $v0, 1
		move $a0, $t0
		syscall

		li $v0, 4
		la $a0, fromCol
		syscall

		# This is temp for col add 1 to it 
		move $t0, $s1
		addiu $t0, $t0, 1
		li $v0, 1
		move $a0, $t0
		syscall

		li $v0, 4
		la $a0, period
		syscall

		# This puts a non zero number into $s2 which means that the puzzle is invalid 
		li $s2, 1

		# This then jumps back to digit loop
		jr $ra


start:
		# a0 holds the number which to multiply by (18 for new row start) (2 for new column start)
		move $t1, $a0		# Moves argument into temp register

		# This then does the row/col * 18/2 and puts value to be added in $v0 to be returned
		mult $s1, $t1
		mflo $v0

		jr $ra


block:
		# We will save the address of numbers in a register as we will add to it
		la $s0, numbers			# This will hold the address for the array as it will reset each time we go through
		
		# This sets to start of block = 54 * Quotient[block-1, 3] + 6*Remainder[block-1]
		#		Recall that $s1 holds the counter for the block and already does the -1 as s1 goes 0-8
		li $t0, 3			# This gets the quotient
		div $s1, $t0		
		mflo $t0

		li $t1, 54			# This gets the first product 
		mult $t0, $t1
		mflo $t0

		li $t1, 3			# This get the remainder
		div $s1, $t1
		mfhi $t1

		li $t2, 6			# This gets the second product
		mult $t1, $t2
		mflo $t1

		addu $t0, $t0, $t1		# This adds two products together
		addu $s0, $s0, $t0		# This adds it to the starting address	

		# This goes into the loop to start looking for digits to compare
		li $s3, 49				# This is the counter for each digit from 1 to 9
		addiu $sp, $sp, -4
		sw $ra, 0($sp)
		jal blockDig
		lw $ra, 0($sp)
		addiu $sp, $sp, 4

		# This branches us to jump if we found the puzzle is invalid by $s2 not equal to zero
		bne $s2, $zero, jump

		# This will then loop back to the block if $s1 is less than 9 
		addiu $s1, $s1, 1		# Iterate through the blocks
		li $t0, 9				# Our temp register to hold 9
		blt $s1, $t0, block		# This branches to blocks

		# $s1 goes from 0 to 8 for the block count and when it gets to 9 we will
		#			return to the main function and continue through that 
		jr $ra


blockDig:
		# Each time we search for a new element we need to start back at the beginning of the row
		#		which is stored in $s0, which we do not want to change. Thus we will set $s5 to
		# 		be $s0 here and then add to it as we go through the row/col in digFind function.
		move $s5, $s0

		# Now we will go into another function that will loop through the row to find the digit we are on
		li $s4, 0			# This will be the counter for each element check in the row
		addiu $sp, $sp, -4
		sw $ra, 0($sp)
		jal blockDigFind
		lw $ra, 0($sp)
		addiu $sp, $sp, 4

		# This branches us to jump if we found the puzzle is invalid by $s2 not equal to zero
		bne $s2, $zero, jump

		# This branches into digit again if $s3 is les than 58
		addiu $s3, $s3, 1			# Iterate through the digits
		li $t1, 58					# Our temp register to hold 58
		blt $s3, $t1, blockDig		# This branches to digit

		jr	$ra


blockDigFind:
		# This branch is to make sure we have gone over the amount of elements in the row
		li $t0, 9				# Our temp register to hold 9
		beq $s4, $t0, misBlock 	# If $s4 gets to 9 that means we haven't found the digit
		addiu $s4, $s4, 1		# Iterate through the elements if we need to go through them all

		# This branch is to compare the digit with the element in check
		lbu $t0, 0($s5)			# This loads the element in the address stored in $s5
		subu $t0, $t0, $s3		# This subtracts the element from the digit
		li $t1, 3
		div $s4, $t1
		mfhi $t1
		beq $t1, $zero, bigAdd	# Goes in if the element we are comparing is the 3rd, 6th or 9th element
		addiu $s5, $s5, 2		# adds 2 only if it does not go into bigAdd 
		bne $t0, $zero, blockDigFind 	# If the difference is zero than they are the same digit and we continue

		jr $ra

bigAdd:
		addiu $s5, $s5, 14
		bne $t0, $zero, blockDigFind
		jr $ra

misBlock:
		# This is invalid because it is missing a digit in the block
		li $v0, 4
		la $a0, missing
		syscall

		# This is temp for digit so we can subtract it to get non ascii value
		move $t0, $s3
		addiu $t0, $t0, -48
		li $v0, 1
		move $a0, $t0
		syscall

		li $v0, 4
		la $a0, fromBlo
		syscall

		# This is temp for block add 1 to it 
		move $t0, $s1
		addiu $t0, $t0, 1
		li $v0, 1
		move $a0, $t0
		syscall

		li $v0, 4
		la $a0, period
		syscall

		# This puts a non zero number into $s2 which means that the puzzle is invalid 
		li $s2, 1

		# This then jumps back to block digit loop
		jr $ra

jump:
		# This is to jump back if we found the puzzle is invalid in one spot
		jr $ra

end:	
		li $v0, 10
		syscall
