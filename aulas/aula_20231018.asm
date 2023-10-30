.include "macros.inc"

.data

.text
# init
init:
	la $sp, 0x7FFFEFFC
	jal main
	exit

# main
# --- old stack  16 ($sp)
#============= 
#  <empty>       12 ($sp)
#-------------
#  $ra            8 ($sp)
#-------------
#  $a1 			  4 ($sp)
#-------------
#  $a0   		  0 ($sp)
#=============
main:
	addi $sp, $sp, -16
	sw   $ra, 8($sp)

	#funcaoA(3,4)
	li $a0, 3
	li $a1, 4
	jal funcaoA
	print_int_reg($v0)
	
	lw   $ra, 8($sp)
	addi $sp, $sp, 16
	jr $ra

# int funcaoA(int a, int b) {
#     int tmp1;
#     tmp1 = funcaoB(a,1);
#     return tmp1 + funcaoB(b,1);
# }

#-------------
#  $a1 (funcaoA)  20 ($sp)
#-------------
#  $a0 (funcaoA)  16 ($sp)
#============= -> old_stack
#  tmp1           12 ($sp)
#-------------
#  $ra            8 ($sp)
#-------------
#  $a1 (funcaoB)  4 ($sp)
#-------------
#  $a0 (funcaoB)  0 ($sp)
#=============
funcaoA:
	addi $sp, $sp, -16
	sw   $ra, 8($sp)
	
	sw   $a1, 20($sp)
	li   $a1, 1
	jal  funcaoB
	sw   $v0, 12($sp) 
	
	lw   $a0, 20($sp)	
	li   $a1, 1
	jal  funcaoB
	
	lw   $t0, 12($sp) 
	add  $v0, $t0, $v0
	
	lw   $ra, 8($sp)
	addi $sp, $sp, 16
	jr   $ra

# int funcaoB(int valor, int shift) {
#     return valor << shift;
# }
funcaoB:
	sllv $v0, $a0, $a1
	jr   $ra

