all:	Vengeance

Vengeance:	main.o  magicmoves.o nonslidingmoves.o movegen.o make_unmake.o utility.o
	clang main.o magicmoves.o nonslidingmoves.o movegen.o make_unmake.o utility.o -O3 -o Vengeance

main.o:	main.c
	clang -c main.c

movegen.o:	movegen.c
	clang -c movegen.c

magicmoves.o:	magicmoves.c
	clang -c magicmoves.c

nonslidingmoves.o:	nonslidingmoves.c
	clang -c nonslidingmoves.c

utility.o:	utility.c
	clang -c utility.c

make_unmake.o:	make_unmake.c
	clang -c make_unmake.c

clean:
	rm *o Vengeance