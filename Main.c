/*
 * Main.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include <stdio.h>
#include "globals.h"

void init();

int main(int argc, char **argv) {

	init(); /* initalize pieceBB array */

	for(int i = 0; i < SIZE; i++) {
		
		printf("%llu\n", pieceBB[i]);
	}


	return 0;
}


void init() {

	/* default positions of pieces on board */

	pieceBB[WHITE_KING] = 0x0000000000000008U;
	pieceBB[WHITE_QUEEN] = 0x0000000000000010U;
	pieceBB[WHITE_BISHOPS] = 0x0000000000000024U;
	pieceBB[WHITE_KNIGHTS] = 0x0000000000000042U;
	pieceBB[WHITE_ROOKS] = 0x0000000000000081U;
	pieceBB[WHITE_PAWNS] = 0x000000000000FF00U;
	pieceBB[WHITE_PIECES] = 0x000000000000FFFFU;

	pieceBB[BLACK_KING] = 0x0800000000000000U;
	pieceBB[BLACK_QUEEN] = 0x1000000000000000U;
	pieceBB[BLACK_BISHOPS] = 0x2400000000000000U;
	pieceBB[BLACK_KNIGHTS] = 0x4200000000000000U;
	pieceBB[BLACK_ROOKS] = 0x8100000000000000U;
	pieceBB[BLACK_PAWNS] = 0x00FF000000000000U;
	pieceBB[BLACK_PIECES] = 0xFFFF000000000000U;

	pieceBB[OCCUPIED_SQUARES] = 0xFFFF00000000FFFFU;
	pieceBB[EMPTY_SQUARES] = 0x0000FFFFFFFF0000U;

}

