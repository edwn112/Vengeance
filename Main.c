/*
 * Main.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include <sys\timeb.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "utility.h"
#include "magicmoves.h"
#include "nonslidingmoves.h"
#include "init.h"
#include "perft.h"

int main(int argc, char **argv) {

	int depth = 0;

	depth = atoi(argv[1]);

	printf("Depth = %d\n", depth);

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

	printf("\n");
	for (int i = 1; i <= depth; i++) {

		ftime(&start);

		nodes = 0;
		quiet = 0;
		cap = 0;
		en = 0;
		cas = 0;
		check = 0;

		color = WHITE;

		nodes = perft(i, color);

		ftime(&end);

		diff = ((1000.0 * (end.time - start.time) 
			+ (end.millitm - start.millitm)) / 1000);
		
		printf("Depth(%d)=   ", i);

		printf("%8llu (%.3f sec), color - %s, quiet - %8llu, captures - %8llu, en - %6llu, cas - %6llu, checks - %8llu\n", nodes, diff, ((color==0) ? "WHITE" : "BLACK"), quiet, cap, en, cas, check);
	}

	return 0;
}


