all: hello writeText compareText

hello: hello.o
	ld -o hello hello.o
hello.o: hello.s
	as -o hello.o hello.s

writeText: writeText.o
	ld -o writeText writeText.o
writeText.o: writeText.s
	as -o writeText.o writeText.s

compareText: compareText.o
	ld -o compareText compareText.o
compareText.o: compareText.s
	as -o compareText.o compareText.s
