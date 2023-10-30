.text
#############################################	
# void changeCase(char * str, bool type);
# 
#}
changeCase:
	changeCase_IF0:
	beqz $a1, changeCase_IF0_lower
	 	li $t0, -32 
	 	li $t1, 97 
		li $t2, 122
		b  changeCase_IF0_end
	changeCase_IF0_lower:
		li $t0, 32 
	 	li $t1, 65 
		li $t2, 90
	changeCase_IF0_end:
	# fazer a conversão para caracteres maiúsculos
	changeCase_L0:
		lb $t3, 0($a0)
		beq $t3, $zero, changeCase_L0_exit
		changeCase_IF1:
			blt  $t3, $t1, changeCase_IF1_end
			bgt  $t3, $t2, changeCase_IF1_end
			add  $t3, $t3, $t0
			sb   $t3, 0($a0)
		changeCase_IF1_end:
		addi $a0, $a0, 1
		j changeCase_L0
	changeCase_L0_exit:
	jr $ra
#############################################

#############################################	
# int strResize(char * str, int size);
#
#  O procedimento deve modificar o tamanho da string
# de acordo com o tamanho especificado pelo parâmetro
# size. O size deve ser sempre menor que o tamanho
# atual da string.
#
#  O procedimento retorna o valor -1, caso o size seja
# maior que o tamanho da string, ou o novo tamanho da
# string, caso contrário, ou seja, o próprio valor de
# size.
#
# 
# $a1 (old_stk) -> 12($sp)
#---------------
# $a0 (old_stk) -> 8($sp)
#===============
# $ra           -> 4($sp)
#---------------
# $a0           -> 0($sp)
#############################################	
strResize:
	addiu $sp, $sp, -8
	sw    $ra, 4($sp)
	sw    $a0, 8($sp)
	
	li $v0, -1
	
	jal strlen
	move $t0, $v0
	
	lw   $a0, 8($sp)
	
	bgt $a1, $t0, strResize_end
	move $v0, $a1
	add $a0, $a0, $a1
	sb  $zero, 0($a0)
strResize_end:
	lw    $ra, 4($sp)
	addiu $sp, $sp, 8
	jr $ra
#############################################

#############################################	
# int strSearch(char * str, char value);
#
#  O procedimento deve procurar o caracter passado
# como parâmetro na string, retornando o inteiro
# equivalente a sua posição na string (índice).
#  Caso o caracter não seja encontrado, o procedimento
# deve retornar -1.
#
strSearch:
	li $v0, -1
	move $t0, $zero
	strSearch_L0:
		lb   $t1, 0($a0)
		beq  $t1, $zero, strSearch_L0_exit
		strSearch_IF0:
			bne  $t1, $a1, strSearch_IF0_end
			move $v0, $t0
			b    strSearch_L0_exit
		strSearch_IF0_end:
		addi $a0, $a0, 1
		addi $t0, $t0, 1
		j strSearch_L0
	strSearch_L0_exit:
strSearch_end:
	jr $ra
#############################################

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
	li $v0, 0 # len = 0
	strlen_L0:
		lb   $t0, 0($a0)
		beq  $t0, $zero, strlen_L0_exit
		addi $a0, $a0, 1
		addi $v0, $v0, 1
		j strlen_L0
	strlen_L0_exit:
	jr $ra
#############################################
