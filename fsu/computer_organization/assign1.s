#############################################################
#															#
#					Colton Piper							#
#	  This is assignment number 1 which prompts the user 	#
#	to enter 2 integers and if one the integers is less 	#
# 	than 1 then print an error that tells the user one of	#
#	the numbers is to low. If not the program then prints	#
#	the addition, difference, product and quotient of the 	#
#	two numbers.											#
#															#
#############################################################


		.data
Title:	.asciiz "Colton Piper, Assignment 1, add, subtract, multiply, and divide two numbers. \n"
Num1:	.asciiz	"Enter the first integer: "
Num2:	.asciiz	"Enter the second integer: "
NEG:	.asciiz "The number is less than 1 \n"
newLine:.asciiz "\n"
EQUAL:	.asciiz " = "
ADD:	.asciiz " + "
DIFF:	.asciiz " - "
MULT:	.asciiz	" * "
DIV:	.asciiz " / "
DIV2:	.asciiz " with a remainder of "
close:	.asciiz " These are the operations with these numbers.\n"
		.align 2
		.text
		.globl main

main:
		# This prints out the Title
		li $v0, 4
		la $a0, Title
		syscall

		# This prints out Num1
		li $v0, 4
		la $a0, Num1
		syscall

		# This takes in Num1, and puts it in register $t1
		li $v0, 5
		syscall
		move $t1, $v0

		# This checks if Num1 is less then
		li $t0, 1
		blt $t1, $t0, Fail

		# This prints out Num2
		li $v0, 4
		la $a0, Num2
		syscall

		# This takes in Num2, and puts it in register $t2
		li $v0, 5
		syscall
		move $t2, $v0

		# This checks if Num2 is less then
		li $t0, 1
		blt $t2, $t0, Fail

		# This does the addition, subtraction, and multiplication
		addu $s0, $t1, $t2
		subu $s1, $t1, $t2
		mult $t1, $t2

		# This prints out the addition
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 4
		la $a0, ADD 
		syscall
		li $v0, 1
		move $a0, $t2
		syscall
		li $v0, 4
		la $a0, EQUAL
		syscall
		li $v0, 1
		move $a0, $s0
		syscall
		li $v0, 4
		la $a0, newLine
		syscall

		# This prints out the subtraction
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 4
		la $a0, DIFF 
		syscall
		li $v0, 1
		move $a0, $t2
		syscall
		li $v0, 4
		la $a0, EQUAL
		syscall
		li $v0, 1
		move $a0, $s1
		syscall
		li $v0, 4
		la $a0, newLine
		syscall

		# This prints out the multiplication
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 4
		la $a0, MULT 
		syscall
		li $v0, 1
		move $a0, $t2
		syscall
		li $v0, 4
		la $a0, EQUAL
		syscall
		li $v0, 1
		mflo $a0
		syscall
		li $v0, 4
		la $a0, newLine
		syscall


		# This is the division
		divu $t1, $t2

		# This prints out the division
		li $v0, 1
		move $a0, $t1
		syscall
		li $v0, 4
		la $a0, DIV
		syscall
		li $v0, 1
		move $a0, $t2
		syscall
		li $v0, 4
		la $a0, EQUAL
		syscall
		li $v0, 1
		mflo $a0
		syscall
		li $v0, 4
		la $a0, DIV2
		syscall
		li $v0, 1
		mfhi $a0
		syscall
		li $v0, 4
		la $a0, newLine
		syscall


		# This prints the closing message
		li $v0, 4
		la $a0, close
		syscall


		li $v0, 10
		syscall

			



Fail: 
		# This prints that the number you have entered is less than 1
		li $v0, 4
		la $a0, NEG
		syscall

		li $v0, 10
		syscall
