#include <stdbool.h>
#include "perft.h"
#include "movegen.h"
#include "make_unmake.h"
#include "utility.h"


u64 perft(u8 depth, u8 Color) {


	u32 move_list[MAX_MOVES];

	u64 nodes = 0;
	u8 n_moves, i;

	if(depth == 0)
		return 1;

	color = Color;

	n_moves = gen_moves(move_list, color);

	for(i = 0; i < n_moves; i++) {
		
		make_move(move_list[i]);	

		if(!is_sq_attacked((bit_scan_forward(piece_bb[color][KING])), color)) {
			nodes += perft(depth - 1, color ^ 1);	
		}
		else
			check += 1;

		unmake_move(move_list[i]);
	}

	return nodes;
}