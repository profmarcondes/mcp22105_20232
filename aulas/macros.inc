.macro print_str_ptr (%ptr)
  li $v0, 4
  la $a0, %ptr
  syscall
.end_macro

.macro print_str (%str)
.data
mStr: .asciiz %str
.text
   li $v0, 4
   la $a0, mStr
   syscall
.end_macro

.macro print_int_reg (%reg)
  move $a0, %reg
  li $v0, 1
  syscall
.end_macro

.macro get_str (%ptr, %max_size)
  li $v0, 8
  la $a0, %ptr
  li $a1, %max_size
  syscall
.end_macro

.macro get_int(%reg)
	li $v0, 5
	syscall
	move %reg, $v0
.end_macro

.macro exit
   li $v0, 10
   syscall
.end_macro