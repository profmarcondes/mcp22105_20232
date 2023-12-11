.include "system.inc"

.data

.text 0x00401000
# main
main:
	li $s0, 0
	
main_loop:
	addi $s0, $s0, 1
	
j main_loop
	
	jr $ra
	
#==============
