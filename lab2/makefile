all: calculator

calculator.o: calculator.s
	as -g --32 -o calculator.o calculator.s

calculator: calculator.o
	ld -m elf_i386 -o calculator calculator.o
