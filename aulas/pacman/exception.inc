.kdata
_kexception_msg:	.word  _e0, _eu, _eu, _eu, _e4,  _e5,  _e6,  _e7
					.word  _e8,  _e9,  _e10,  _eu,  _e12,  _e13,  _eu,  _e15
              
_eu: .asciiz	"Exception Unknow \n"
_e0: .asciiz	"Hardware Interrupt \n"
_e4: .asciiz	"Address error exception caused by load or fetch instruction \n"
_e5: .asciiz	"Address error exception caused by store instruction \n"
_e6: .asciiz	"Bus error on instruction fetch \n"
_e7: .asciiz	"Bus error on data fetch \n"
_e8: .asciiz	"System call exception \n"
_e9: .asciiz	"Breakpoint exception \n"
_e10: .asciiz	"Reserved Instruction exception \n"
_e12: .asciiz	"Arithmetic Overflow \n"
_e13: .asciiz	"Trap instruction exception \n"
_e15: .asciiz	"Floating point exception caused by floating point instruction \n"
 
 
.ktext 0x80000180
exception_handler:
	addi  $k0, $k0, -124
	sw    $at, 0($k0)
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
	
	### Tratamento das exceções/interrupções
	
    # Identificar a causa da excecão/interrupcão
	mfc0 	    $t0, $13
	andi		$t0, $t0, 0x007C
	la  		$t1, _kexception_msg
	add 		$t1, $t1, $t0
	lw 		    $a0, 0($t1)
	li 		    $v0, 4
	syscall
	
	#Verifica interrupção de hardware
	srl 		$t0, $t0, 2
	beqz 		$t0, exception_handler_Hardware

	bge  		$t0, 8, exception_handler_SoftException
	
exception_kernel_panic:
	li 			$v0, 10
	syscall
	
exception_handler_SoftException:
	mfc0  	$t0, $14      # $k0 = EPC 
    addiu 	$t0, $t0, 4   # Increment $k0 by 4 
    mtc0  	$t0, $14      # EPC = point to next instruction
    j		exception_handler_Done 

exception_handler_Hardware:
	# Chama getchar para ler tecla digitada e escreve
	# no ringbuffer do teclado
	# IMP
	
exception_handler_Done:

	# Clear Cause register
	mtc0		$0, $13	
		
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
	lw    $k1, 116($k0)
	mthi  $k1
	lw    $k1, 120($k0) 
	mtlo  $k1

	addi  $k0, $k0, 124

	eret
	

