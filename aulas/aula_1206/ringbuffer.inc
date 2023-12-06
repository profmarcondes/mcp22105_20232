#define MAX_SIZE 16
.eqv RB_MAX_SIZE 16

#typedef struct ringbuffer {
#	int size;
#	int rd;
#	int wr;
#	char buf[MAX_SIZE];
#} t_ringbuffer;

.macro t_ringbuffer(%name)
.data
%name:
.align 2
	.space 12
	.space RB_MAX_SIZE
.end_macro

.text 0x00430000
# void rb_init(t_ringbuffer * rbuf){
# 	rbuf->size = 0;
# 	rbuf->rd = 0;
# 	rbuf->wr = 0;
# }
rb_init:

	jr $ra

# bool rb_empty(t_ringbuffer * rbuf){
#	if (rbuf->size == 0) {
#		return 1;
#	} else {
#		return 0;
#	}
# }
rb_empty:

	jr   $ra

# bool rb_full(t_ringbuffer * rbuf){
#	if (rbuf->size == MAX_SIZE)
#		return 1;
#	else
#		return 0;
# } 
rb_full:

	jr   $ra
	
#char rb_read(t_ringbuffer * rbuf){
#	char tmp = 0;
#	if(!rbuf_empty(rbuf)){
#		rbuf->size--;
#		tmp = rbuf->buf[rbuf->rd];
#		rbuf->rd = (rbuf->rd + 1) % MAX_SIZE;
#	}
#	return tmp;
#}
rb_read:

	jr $ra

# bool rb_write(t_ringbuffer * rbuf, char byte){
#	if(!rbuf_full(rbuf)){
#		rbuf->size++;
#		rbuf->buf[rbuf->wr] = byte;
#		rbuf->wr = (rbuf->wr + 1) % MAX_SIZE;
#		return 1;
#	}
#	return 0;
# }
rb_write:

	jr $ra
