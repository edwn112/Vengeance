all:	Vengeance

Vengeance:	main.o  magicmoves.o nonslidingmoves.o movegen.o utility.o
	clang main.o magicmoves.o nonslidingmoves.o movegen.o utility.o -o Vengeance

main.o:	main.c
	clang -c main.c

movegen.o:	movegen.c
	clang -c movegen.c

magic_moves.o:	magicmoves.c
	clang -c magicmoves.c

nonslidingmoves.o:	nonslidingmoves.c
	clang -c nonslidingmoves.c

utility.o:	utility.c
	clang -c utility.c

clean:
	rm *o Vengeance