all:	Vengeance

Vengeance:	main.o  magic_moves.o movegen.o utility.o
	clang main.o magic_moves.o movegen.o utility.o -o Vengeance

main.o:	main.c
	clang -c main.c

movegen.o:	movegen.c
	clang -c movegen.c

magic_moves.o:	magic_moves.c
	clang -c magic_moves.c

utility.o:	utility.c
	clang -c utility.c

clean:
	rm *o Vengeance