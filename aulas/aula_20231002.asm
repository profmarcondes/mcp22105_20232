.include "macros.inc"

.data
c: .word 0
msg1: .asciiz "A soma dos quadrados é: "
msg2: .asciiz "strlen="
newline: .asciiz "\n"

.text
main:
	la $gp, 0x10010000
	
	# c = sumOfSquare(3,5)
	li $a0, 3
	li $a1, 5
	jal sumOfSquares
	sw $v0, 0($gp) # c = sumOfSquares
	move $t0, $v0

	print_str_ptr(msg1)
	print_int_reg($t0)
	
	print_str_ptr(newline)
	
	li $a0, 2
	li $a1, 6
	jal sumOfSquares
	move $s0, $v0
	print_str_ptr(msg1)
	print_int_reg($s0)
	
	print_str_ptr(newline)
	
	la $a0, msg1
	jal strlen
	move $s0, $v0
	
	print_str_ptr(msg2)
	print_int_reg($s0)
	
	exit
	
# int sumOfSquares(int a, int b)
sumOfSquares:
	mul	$t0, $a0, $a0 # t0 = a*a
	mul $t1, $a1, $a1 # t1 = b*b
	add $v0, $t0, $t1 # v0 = a*a + b*b
	jr  $ra	
	
#############################################	
# int strlen(char * str) {
#   int len = 0;
#   while ( *str != 0 ){
#     str = str + 1;
#     len = len + 1;
#   }
#   return len;
#}
strlen:
	li $v0, 0
	strlen_L0:
		lb $t0, 0($a0)
		beq $t0, $zero, strlen_L0_end
			addi $a0, $a0, 1 # str++
			addi $v0, $v0, 1
		j strlen_L0
	strlen_L0_end:
	jr $ra
#############################################


