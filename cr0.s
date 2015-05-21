/*
 *	cr0.s
 *
 *	This program shows how to display the initial contents of 
 *	the processor's cr0 register as a 32-bit binary value.
 *
 *	        assemble using:  $ as cr0.s -o cr0.o
 *	        and link using:  $ ld cr0.o -o cr0
 *
 *	However, cr0 access requires privilege level 0, so this has
 *	been replaced with cr0.c
 *
 *	Updated for kernel 3.13.0-39
 */
	.code32
	.equ		sys_write, 4
	.equ		sys_exit,  1
	.equ		device_ID, 1

	.section	.data
msg:	.ascii		"\n\tcr0="
buf: 	.ascii		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n\n"
len:	.int		. - msg

	.section	.text
_start:
	# read cr0 into register EDX
	movl		%cr0, %edx

	# counted loop: generate the 32 binary digits 
	movl		$buf, %ebx
	movl		$32, %ecx
again:
	movb		$0, %al
	addl		%edx, %edx
	adcb		$'0', %al
	movb		%al, (%ebx)
	incl		%ebx
	decl		%ecx
	jnz		again

	# write our message to the display device
	movl		$sys_write, %eax
	movl		$device_ID, %ebx
	movl		$msg, %ecx
	movl		len, %edx
	int		$0x80

	# terminate this program
	movl		$sys_exit, %eax
	movl		$0, %ebx
	int		$0x80

	.global		_start
	.end

