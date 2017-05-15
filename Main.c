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

	nodes1 = 0;
	quiet = 0;
	cap = 0;
	en = 0;
	cas = 0;

	struct timeb start, end;
	double diff;

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
	
	u8 i;
	u64 nodes;

	COLOR = WHITE;

	printf("Enter\n");

	i = 0;

	while(i < MAX_DEPTH) {

		printf("\n\n");
		
		ftime(&start);

		nodes = perft(i);

		ftime(&end);

		diff = ((1000.0 * (end.time - start.time) 
			+ (end.millitm - start.millitm)) / 1000);
		
		printf("Depth - %d\n", i);

		printf("color - %d, checks - %llu, quiet - %llu, captures - %llu\n", COLOR, check, quiet, cap);
	

		printf("%llu nodes searched and operation took %.3f seconds\n", nodes, diff);

		i++;
	}

	return 0;
}


