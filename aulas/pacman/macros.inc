.macro syscall_exit
	li $v0, 10
	syscall
.end_macro

.macro syscall_exit (%status)
    li $v0, 17
    add $a0, $zero, %status
    syscall
.end_macro

.macro syscall_sleep (%milli)
    li $v0, 32
    add $a0, $zero, %milli
    syscall
.end_macro

.macro syscall_print_intReg (%intReg)
    li $v0, 1
    add $a0, $zero, %intReg
    syscall
.end_macro

.macro  syscall_print_intMem (%intPtr)
	li   $v0, 1
	lw   $a0, %intPtr
	syscall
.end_macro

.macro syscall_print_charReg (%char)
    li $v0, 11
    add $a0, $zero, %char
    syscall
.end_macro

.macro syscall_print_charMem (%charPtr)
    li $v0, 11
    lw   $a0, %charPtr
    syscall
.end_macro

.macro syscall_print_str (%str)
.data 
mStr: .asciiz %str
.text
    li $v0, 4
    la $a0, mStr
    syscall
.end_macro

.macro syscall_print_strMem (%strPtr)
	li $v0, 4
	la $a0, %strPtr
	syscall
.end_macro

.macro syscall_get_intReg (%reg)
	li $v0, 5
	syscall
	move %reg, $v0
.end_macro

.macro syscall_get_intMem (%x)
	li $v0, 5
	syscall
	sw $v0, %x
.end_macro

.macro syscall_get_strMem (%strPtr, %buf_size)
	li $v0, 8
	la $a0, %strPtr
	li $a1, %buf_size
	syscall
.end_macro