.code32
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

.global _start

.text
msg_calc: .ascii "Wybierz operacje (+,-,*,/): "
msg_calclen = . - msg_calc

.data
buf: .ascii " "
buf_len = . - buf

zaokraglenie: .short 0xc00 #0x000 najblizsze, 0x400 - -inf, 0x800 +inf, 0xc00 - obciecie
pojedyncza: .short 0x000 #0x000 pojedyncza, 0x200 - podwojna
slowo_sterujace: .short 0x103F

liczba1: .float 1.0000
liczba2: .float 0.2222


_start:
mov zaokraglenie, %eax
mov pojedyncza, %ebx
mov slowo_sterujace, %ecx
add %eax, %ebx
add %ebx, %ecx
mov %ecx, slowo_sterujace
fldcw slowo_sterujace

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg_calc, %ecx
mov $msg_calclen, %edx
int $0x80

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov buf(,%edi,1), %al


float:
cmp $43, %al #+
je add

cmp $45, %al #-
je sub

cmp $42, %al #*
je mul

cmp $47, %al #/ 
je div
jmp end

add:
	flds liczba1
	fadd liczba2
	jmp end
sub:
	flds liczba1
	fsub liczba2
	jmp end
mul:
	flds liczba1
	fmul liczba2
    	jmp end
div:
	flds liczba1
	fdiv liczba2
    	jmp end



end:
mov $1, %eax
mov $0, %ebx
int $0x80
