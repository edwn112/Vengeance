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

	hist_add.move = 0;
	hist_add.ep_flag = 0;
	hist_add.castle_flags = (u8)0x1111;  

	hist[ply] = hist_add;
	
	u8 i, nodes;

	COLOR = 1;

//	for(i = 0; i < MAX_DEPTH; i++) {

		u8 depth;
		scanf("%u", &depth);

		ftime(&start);

		nodes = perft(depth);

		ftime(&end);

		diff = (u8)(1000.0 * (end.time - start.time) 
			+ (end.millitm - start.millitm));

		printf("Nodes - %u and operation took %u milliseconds\n", nodes, diff);
//	}

	return 0;
}


