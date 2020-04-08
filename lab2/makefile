all: add sub mul

add: add.o
	ld -m elf_i386 -o add add.o
add.o: add.s
	as --32 -o add.o add.s -g

sub: sub.o
	ld -m elf_i386 -o sub sub.o
sub.o: sub.s
	as --32 -o sub.o sub.s -g

mul: mul.o
	ld -m elf_i386 -o mul mul.o
mul.o: mul.s
	as --32 -o mul.o mul.s -g
