.include "macros.inc"

.data

.text
# init
init:
	la $sp, 0x7FFFEFFC
	jal main
	exit

# main
main:

	li $t1, 0xFFFFFFFF
	addi $t0, $t1, 1

	li $t1, 0x7FFFFFFF
	addi $t0, $t1, 1

	li $t1, 0x10010001
	lw $t0, 0($t1)
	sw $t0, 0($t1)

	jr $ra
#==============
.eqv KSTACK_SIZE 4096

.ktext 0x80000180
	add   $k1, $at, $zero  
	la    $k0, kstack
	addi  $k0, $k0, KSTACK_SIZE
	
	addi  $k0, $k0, -124
	sw    $k1, 0($k0)
	sw    $v0, 4($k0)
	sw    $v1, 8($k0)
	sw    $a0, 12($k0)
	sw    $a1, 16($k0)
	sw    $a2, 20($k0)
	sw    $a3, 24($k0)
	sw    $t0, 28($k0)
	sw    $t1, 32($k0)
	sw    $t2, 36($k0)
	sw    $t3, 40($k0)
	sw    $t4, 44($k0)
	sw    $t5, 48($k0)
	sw    $t6, 52($k0)
	sw    $t7, 56($k0)
	sw    $s0, 60($k0)
	sw    $s1, 64($k0)
	sw    $s2, 68($k0)
	sw    $s3, 72($k0)
	sw    $s4, 76($k0)
	sw    $s5, 80($k0)
	sw    $s6, 84($k0)
	sw    $s7, 88($k0)
	sw    $t8, 92($k0)
	sw    $t9, 96($k0)
	sw    $gp, 100($k0)
	sw    $sp, 104($k0)
	sw    $fp, 108($k0)
	sw    $ra, 112($k0)
	mfhi  $t0
	sw    $t0, 116($k0)
	mflo  $t0
	sw    $t0, 120($k0) 
	
	la    $a0, kmsg1    # $a0 = address of kmsg1 
	li    $v0, 4        # $v0 = service 4 
	syscall             # Print kmsg1
	
	mfc0  $k1, $14
	addi  $k1, $k1, 4
	mtc0  $k1, $14
	
	lw    $k1, 0($k0)
	lw    $v0, 4($k0)
	lw    $v1, 8($k0)
	lw    $a0, 12($k0)
	lw    $a1, 16($k0)
	lw    $a2, 20($k0)
	lw    $a3, 24($k0)
	lw    $t0, 28($k0)
	lw    $t1, 32($k0)
	lw    $t2, 36($k0)
	lw    $t3, 40($k0)
	lw    $t4, 44($k0)
	lw    $t5, 48($k0)
	lw    $t6, 52($k0)
	lw    $t7, 56($k0)
	lw    $s0, 60($k0)
	lw    $s1, 64($k0)
	lw    $s2, 68($k0)
	lw    $s3, 72($k0)
	lw    $s4, 76($k0)
	lw    $s5, 80($k0)
	lw    $s6, 84($k0)
	lw    $s7, 88($k0)
	lw    $t8, 92($k0)
	lw    $t9, 96($k0)
	lw    $gp, 100($k0)
	lw    $sp, 104($k0)
	lw    $fp, 108($k0)
	lw    $ra, 112($k0)
	lw    $t0, 116($k0)
	mthi  $t0
	lw    $t0, 120($k0) 
	mtlo  $t0

	addi  $k0, $k0, 124

	eret
	
.kdata
kmsg1: .asciiz "Ocorreu uma exceção\n"
.align 2
kstack: .space KSTACK_SIZE




