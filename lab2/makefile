all: add sub mul

add: add.o
	ld -o add add.o
add.o: add.s
	as -o add.o add.s -g

sub: sub.o
	ld -o sub sub.o
sub.o: sub.s
	as -o sub.o sub.s -g

mul: mul.o
	ld -o mul mul.o
mul.o: mul.s
	as -o mul.o mul.s -g