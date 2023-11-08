.include "macros.inc"

.data

.text
# init
init:
	la $sp, 0x7FFFEFFC
	jal main
	exit

# main
# --- old stack   8 ($sp)
#============= 
#  <empty>        4 ($sp)
#-------------
#  $ra            0 ($sp)
#=============
main:
	addi $sp, $sp, -8
	sw   $ra, 0($sp)
	
main_L0:
	jal getchar
	move $a0, $v0
	jal printchar
	j   main_L0
	
	lw   $ra, 0($sp)
	addi $sp, $sp, 8
	jr $ra
#==============

#=============================================================
#char getchar();
getchar:
	la $t0, 0xFFFF0000
	
getchar_pooling:
	lw $t1, 0($t0)    # Carregando em $t1, registrador de controle
	andi $t1, $t1, 1  # Isolando o bit 1 do registrador de controle
	beqz $t1, getchar_pooling

	lw $v0, 4($t0)    # carregando valor do registrador de DADOS
	jr $ra
#=============================================================

#=============================================================
# void printchar(char a)
printchar:
	la $t0, 0xFFFF0008
	
printchar_pooling:
	lw $t1, 0($t0)    # Carregando em $t1, registrador de controle
	andi $t1, $t1, 1  # Isolando o bit 1 do registrador de controle
	beqz $t1, printchar_pooling

	sw $a0, 4($t0)    # carregando valor no registrador de DADOS

	jr $ra
#=============================================================





