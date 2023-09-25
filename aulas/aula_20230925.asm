.data
notas:   .float  3.75, 4.87, 9.32
div3:    .float  3.00
msg:     .asciiz "Aprovado - "
msg2:    .asciiz "Reprovado - "      
          
.text

la $gp, 0x10010000

lwc1 $f0, 0($gp)
lwc1 $f1, 4($gp)
lwc1 $f2, 8($gp)

add.s $f3, $f0, $f1
add.s $f3, $f3, $f2

li      $t0, 3
mtc1    $t0, $f4
cvt.s.w $f4, $f4

div.s $f3, $f3, $f4

li      $t0, 6
mtc1    $t0, $f5
cvt.s.w $f5, $f5

c.lt.s 2, $f3, $f5
if:
bc1t 2, reprovado
	la $a0, msg
j end
reprovado:
	la $a0, msg2
end:

li $v0, 4
syscall 

mov.s $f12, $f3
li $v0, 2
syscall


