.include "syscalls.inc"
.include "ringbuffer.inc"
.include "exception.inc"

.eqv  STACK_INIT  0x7FFFEFFC
.eqv  KSTACK_INIT 0x90010000

.text 0x00400000 ## System Init Code
init:
	la $sp, STACK_INIT
	la $k0, KSTACK_INIT
	
	#habilitar interrupções do teclado
	mfc0 $t1, $12
	andi $t1, $t1, 0xFFFE 
	mtc0 $t1, $12
	
	la  $t0, 0xFFFF0000
	lw  $t1, 0($t0)
	ori $t1, $t1, 2
	sw  $t1, 0($t0)
	
	mfc0 $t1, $12
	ori  $t1, $t1, 1 
	mtc0 $t1, $12
	
	jal 	main
	
	syscall_exit
  		
.text 0x00420000  ## System lib
#=============================================================
# char getchar();
getchar:
	la $t0, 0xFFFF0000   # Keyboard device base address
getchar_L0:
	lw   $t1, 0($t0)     # Load Keyboard Control Reg
	andi $t1, $t1, 0x01  # Isolo o bit 1
	beqz $t1, getchar_L0 # Se bit == 0, volto
	
	lb	$v0, 4($t0)		# Carrego o Keyboard Data

    jr $ra
#=============================================================

#=============================================================
# void putchar(char value);
putchar:
	la $t0, 0xFFFF0008   # Display device base address
putchar_L0:
	lw   $t1, 0($t0)     # Load Display Control Reg
	andi $t1, $t1, 0x01  # Isolo o bit 1
	beqz $t1, putchar_L0 # Se bit == 0, volto
	
	sb	$a0, 4($t0)		# Carrego o Display Data

    jr $ra
#=============================================================
