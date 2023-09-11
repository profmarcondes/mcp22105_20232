.macro print_strPtr (%ptr)
	li $v0, 4
	la $a0, %ptr
	syscall
.end_macro

.macro exit
  li $v0, 10
  syscall
.end_macro

.macro getInt(%reg)
	li $v0, 5
	syscall
	move %reg, $v0
.end_macro


.data

jump_table: .word case_0, case_1, case_2, case_3, case_4
		    .word case_5, case_6, case_7, case_8, case_9

question: .asciiz "Digite um número: "
n_zero: .asciiz "n é zero\n"
n_par: .asciiz "n é par\n"
n_quadrado: .asciiz "n é quadrado\n"
n_primo: .asciiz "n é primo\n"
n_default: .asciiz "fora da faixa [ 0 - 9 ]\n"

.text


main:

print_strPtr(question)
getInt($s0)

bne $s0, 99, skip
	exit
skip:

# switch
bgtu $s0, 9, default
la $t0, jump_table
sll $t1, $s0, 2 ## $s0 * 4
add $t0, $t0, $t1 ## &jump_table[i]
lw  $t2, 0($t0)
jr  $t2

case_0:
	print_strPtr(n_zero)
	j switch_end
case_4:
	print_strPtr(n_par)
case_1:
case_9:
	print_strPtr(n_quadrado)
	j switch_end
case_2:
	print_strPtr(n_par)
case_3:
case_5:
case_7:
	print_strPtr(n_primo)
	j switch_end
case_6:
case_8:
	print_strPtr(n_par)
	j switch_end
default:
	print_strPtr(n_default)
switch_end:

j main



