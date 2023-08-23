
.macro exit
	li $v0, 10
	syscall
.end_macro

.macro imprime_inteiro (%reg)
	li $v0, 1
	move $a0, %reg
	syscall
.end_macro

.data
nums:   .word -7, 20, -5
result: .word

.text
lui $gp, 0x1001
lh  $s1, 0($gp) 
lw  $s2, 4($gp)
lw  $s3, 8($gp)

imprime_inteiro($s1)
imprime_inteiro($s2)
imprime_inteiro($s3)

add $s1, $s1, $s2
add $s1, $s1, $s3

sw  $s1, 12($gp)
imprime_inteiro($s1)

exit






