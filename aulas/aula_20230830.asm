.data
a: .word 4  # 0x10010000
b: .word 6  # 0x10010004
size: .word # 0x10010008

ptr_vector: .word vectorB

.data 0x10010100
vectorA: .word 10, 5 , 6, 78, 92, 53
vectorB: .word 10, 5 , 6, 78, 92, 53


.text

	la $gp, 0x10010000
	lw $s0, 0($gp)  #  $s0 <- a
	lw $s1, 4($gp)  #  $s1 <- b
	
	#IF0
		bne $s0, 10, IF0_then
		#else
		L0: move $t0, $s0 # 
			addi $s0, $s0, -1 # a - 1
			beq  $t0, $zero, L0_end
			# corpo do while
			  #IF1 
			  beq $s1, $zero, L0_end
			  sub $s1, $s1, $s0  ## b -= a
			j L0
		L0_end:
		j IF0_end
	IF0_then:
	    #then
	    li $s1, 9 # b = 9;
	    # init
	    li $t0, 0 # int i = 0
	    L1: bge $t0, $s0, L1_end #cond
	    	#corpo for
	    	add $s1, $s1, $t0
	    	#update
	    	addi $t0, $t0, 1
	    	j L1
	    L1_end:
	IF0_end:
		
	
# if (a != 10) {
#	b = 9;
#	for (int i = 0; i < a; i++) {
#		b += i;
#	}
# } else {
#	while(a--) {
#		if (b == 0){
#		   break;
#		}
#		b -= a;
#	}
# }




