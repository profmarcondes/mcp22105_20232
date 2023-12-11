.text 0x00410000
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
#  OLD_STACK_FRAME   
#  $a1                                 12
# ------------------------------ #
#  $a0                                 8
#==================# 
#  $ra                                 4
# ------------------------------ #
#  $a0                                0
#==================# 
strResize:
		addiu $sp, $sp, -8
		sw     $ra, 4($sp)
		sw     $a0, 8($sp)
		sw     $a1, 12($sp)	

		jal strlen
		lw  $a0,  8($sp)
		lw  $a1,  12($sp)
		
		blt $v0, $a1, strResize_erro
		addu $t0, $a0, $a1
		sb $zero, 0($t0)
		move $v0, $a1
		b strResize_end
strResize_erro:
	     li $v0, -1
strResize_end:  
	    
	lw       $ra, 4($sp)	
	addiu $sp, $sp, 8
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
	li $v0, 0 # len = 0;
strlen_L0:
	lb $t0, 0($a0)
	beqz $t0, strlen_L0_end
	addi $v0, $v0, 1 # len++;
	addi $a0, $a0, 1 # str++;
	j strlen_L0
strlen_L0_end:
	jr $ra
###########################################