.section .data
liczba1:
    .long 0x10304008, 0x701100FF, 0x45100020, 0x08570030
    liczba1_len =(.-liczba1)
    liczba1_rel = liczba1_len / 4
liczba2:
    .long 0xf040500C, 0x00220026, 0x321000CB, 0x04520031
    liczba2_len =(.-liczba2)
    liczba2_rel = liczba2_len / 4


.section .bss


bufor:
    .space 4  

.section .text
.global _start
_start:

clc
pushf
movl $liczba1_rel, %esi


loop:
	popf
  	dec %esi
   	movl liczba1(, %esi, 4), %eax
    	adcl liczba2(, %esi, 4), %eax
    	pushf
	cmp $0, %esi
	jz koniec
	cmp $0, %ebx
	jz koniec
	jmp loop

dodajcarry:
movl $1, bufor
movl $1,(%r10)

koniec:
popf
jc dodajcarry




mov $1, %eax
mov $0, %ebx
int $0x80


