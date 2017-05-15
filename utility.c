#include <stdlib.h>
#include <stdio.h>

#include "utility.h"
#include "nonslidingmoves.h"
#include "magicmoves.h"

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
				putchar('.');
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

/* function to check if a square is attacked */

bool is_sq_attacked(u8 sq, const u8 color) {

	u64 attacks;	
	
	/* check if a king is attacking a sq */

	attacks = get_king_attacks(sq);

	if(attacks & piece_bb[color ^ 1][KING])
		return true;


	/* check if a queen is attacking a sq */

	attacks = Qmagic(sq, occupied);

	if(attacks & piece_bb[color ^ 1][QUEEN])
		return true;

	/* check if a bishop is attacking a square */

	attacks = Bmagic(sq, occupied);

	if(attacks & piece_bb[color ^ 1][BISHOPS])
		return true;

	/* check if a knight is attacking a square */

	attacks = get_knight_attacks(sq);

	if(attacks & piece_bb[color ^ 1][KNIGHTS])
		return true;

	/* check if a rook is attacking a square */

	attacks = Rmagic(sq, occupied);

	if(attacks & piece_bb[color ^ 1][ROOKS])
		return true;

	/* check if a pawn is attacking a square */

	u64 sq_bb = index_bb[sq];

	attacks = (sq_bb << 7) >> (14 * color) | (sq_bb << 9) >> (16 * color);

	if(attacks & piece_bb[color ^ 1][PAWNS])
		return true;

	return false;
}