.include "macros.inc"

.data
msg1: .asciiz "Digite o valor de A: "
msg2: .asciiz "Digite o valor de B: "
msg3: .asciiz "O MDC de A,B é = "

	
.text
# init
init:
	la $sp, 0x7FFFEFFC
	jal main
	exit

# main
# --- old stack   24 ($sp)
#============= 
#  $ra            20 ($sp)
#-------------
#  $s2            16 ($sp)
#-------------
#  $s1            12 ($sp)
#-------------
#  $s0            8 ($sp)
#-------------
#  $a1            4 ($sp)
#-------------
#  $a0            0 ($sp)
#=============
main:
	addi $sp, $sp, -24
	sw   $ra, 20($sp)
	sw   $s0,  8($sp)
	sw   $s1, 12($sp)
	sw   $s2, 16($sp)
	
	print_str("Digite o valor de A: ")
	get_int($s0)
	
	print_str("Digite o valor de B: ")
	get_int($s1)
	
	move $a0, $s0
	move $a1, $s1
	jal  mdc
	move $s2, $v0
	
	print_str("O MCD(")
	print_int_reg($s0)
	print_str(",")
	print_int_reg($s1)
	print_str(") = ")
	print_int_reg($s2)
	print_str("\n")
	
		
	lw   $ra, 20($sp)
	lw   $s0,  8($sp)
	lw   $s1, 12($sp)
	lw   $s2, 16($sp)
	addi $sp, $sp, 24
	
	jr $ra
#==============

# int mdc(int a, int b){
#	if(b == 0) {
#		return a;
#	} else  {
#		return mdc(b, a % b);
#	}
# }

# --- old stack   16 ($sp)
#============= 
#  <empty>        12 ($sp)
#-------------
#  $ra            8 ($sp)
#-------------
#  $a1            4 ($sp)
#-------------
#  $a0            0 ($sp)
#=============
mdc:
	# criar quadro
	addi $sp, $sp, -16
	sw   $ra, 8($sp)
	
	move $v0, $a0
	beqz $a1, mdc_end
	
	div  $a0, $a1
	move $a0, $a1
	mfhi $a1
	jal  mdc
	
mdc_end:
	# destruir quadro
	lw   $ra, 8($sp)
	addi $sp, $sp, 16
	jr $ra
