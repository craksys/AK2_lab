all: add

add.o: add.s
	as -g --32 -o add.o add.s

add: add.o
	ld -m elf_i386 -o add add.o

