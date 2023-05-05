.code32

.text
.data
liczba1:
	.long 0x10304008, 0x701100FF, 0x45100020, 0x08570030
liczba1_len = (. - liczba1)/4
liczba2:
	.long 0xF040500C, 0x00220026, 0x321000CB, 0x04520031
liczba2_len = (. - liczba2)/4

.global _start
_start:

	movl $liczba1_len, %edi
	movl $liczba2_len, %esi
	clc
	jmp addwithoutpop
	
add:

	popf
	
addwithoutpop:

	dec %esi
	dec %edi
	mov liczba1(,%edi,4), %eax
	adc liczba2(,%esi,4), %eax
	pushl %eax
	pushf
	cmpl $0, %edi
	jz addedi
	cmpl $0, %esi
	jz addesi
	jmp add
	
addedi:
	cmpl $0, %esi
	jz quit
	dec %esi
	popf
	movl liczba2(,%esi,4), %eax
	adcl $0, %eax
	pushl %eax
	pushf
	jmp addedi
	
addesi:
	cmpl $0, %edi
	jz quit
	dec %edi
	popf
	movl liczba1(,%esi,4), %eax
	adcl $0, %eax
	pushl %eax
	pushf
	jmp addesi
	
carry:

	push $1
	jmp end
	
quit:

	popf
	jc carry
	
end:

	mov $1, %eax
	mov $0, %ebx
	int $0x80
