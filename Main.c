/*
 * Main.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include <sys\timeb.h>

#include "globals.h"
#include "utility.h"
#include "magicmoves.h"
#include "nonslidingmoves.h"
#include "init.h"
#include "perft.h"

int main(int argc, char **argv) {

	struct timeb start, end;
	u8 diff;

	init_piece_bb(); 
	init_index_bb();
	init_king_attacks();
	init_knight_attacks();
	init_magic_moves(); 

	ply = 0;

	hist[ply].move = 0;
	hist[ply].ep_flag = 0;
	hist[ply].castle_flags = (u8)0x1111;  

	u8 i, nodes;

	COLOR = 1;

//	for(i = 0; i < MAX_DEPTH; i++) {
		ftime(&start);

		nodes = perft(3);

		ftime(&end);

		diff = (u8)(1000.0 * (end.time - start.time) 
			+ (end.millitm - start.millitm));

		printf("Nodes - %u and operation took %u milliseconds\n", nodes, diff);
//	}

	return 0;
}


