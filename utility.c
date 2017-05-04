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


/**
 *  * bitScanForward
 *   * @author Kim Walisch (2012)
 *    * @param bb bitboard to scan
 *     * @precondition bb != 0
 *      * @return index (0..63) of least significant one bit
 *       */

const int index64[64] = {
	 0, 47,  1, 56, 48, 27,  2, 60,
	57, 49, 41, 37, 28, 16,  3, 61,
	54, 58, 35, 52, 50, 42, 21, 44,
	38, 32, 29, 23, 17, 11,  4, 62,
	46, 55, 26, 59, 40, 36, 15, 53,
	34, 51, 20, 43, 31, 22, 10, 45,
	25, 39, 14, 33, 19, 30,  9, 24,
	13, 18,  8, 12,  7,  6,  5, 63
};

int bit_scan_forward(u64 board) {
	const u64 debruijn64 = 285870213051386505U;
	
	return index64[((board ^ (board - 1)) * debruijn64) >> 58];
}