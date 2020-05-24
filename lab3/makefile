all: fpcalc

fpcalc: fpcalc.o
	ld -m elf_i386 -o fpcalc fpcalc.o
fpcalc.o : fpcalc.s
	as --32 -o fpcalc.o fpcalc.s -g
