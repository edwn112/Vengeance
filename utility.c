#include "utility.h"
#include <stdlib.h>
#include <stdio.h>

void print_bb(u64 board) {

	char *output = malloc(65*sizeof(char));
	printf(" ---------- ");
	int row;
	int col;
	for (row=7;row>=0; row--) {
		printf("\n|%d ", row+1);
		for (col=0; col<8; col++) {
			if ((((u64)1)<<((row*8+col)) & board) == (u64)1<<(row*8+col))
				putchar('X');
			else
				putchar('_');
		}
		printf("|");
	}
	printf("\n|  abcdefgh|\n");
	printf(" ---------- \n");
}