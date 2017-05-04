all:	Vengeance

Vengeance:	main.o movegen.o utility.o
	clang main.o movegen.o utility.o -o Vengeance

main.o:	main.c
	clang -c main.c

movegen.o:	movegen.c
	clang -c movegen.c

utility.o:	utility.c
	clang -c utility.c

clean:
	rm *o Vengeance