/*
 * Main.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include <sys\timeb.h>

#include "globals.h"
#include "utility.h"
#include "movegen.h"
#include "magicmoves.h"
#include "nonslidingmoves.h"
#include "init.h"

int main(int argc, char **argv) {

	struct timeb start, end;
	u8 diff;

	init_piece_bb(); 
	init_index_bb();
	init_king_attacks();
	init_knight_attacks();
	init_magic_moves(); 

	u32 move_list[MAX_MOVES];
	ply = 0;

	hist[ply].move = 0;
	hist[ply].ep_flag = 0;
	hist[ply].castle_flags = (u8)0x1111;  

	ftime(&start);
	
	u8 nodes = gen_moves(&move_list[0]);

	int i;
	for(i = 0; i < nodes; i++) {
		printf("\n%d\n", i);
	}

	ftime(&end);
	diff = (u8)(1000.0 * (end.time - start.time) 
		+ (end.millitm - start.millitm));

	printf("Operation took %u milliseconds\n", diff);

	return 0;
}


