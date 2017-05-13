#include <stdbool.h>
#include "perft.h"
#include "movegen.h"
#include "make_unmake.h"

u64 perft(u8 depth) {

	u32 move_list[MAX_MOVES];

	u64 nodes = 0;
	u8 n_moves, i;

	bool is_valid_move;

	if(depth == 0)
		return 1;

	n_moves = gen_moves(move_list);

	for(i = 0; i < n_moves; i++) {
		is_valid_move = make_move(move_list[i]);

		if(is_valid_move)
			nodes += perft(depth - 1);

		unmake_move();
	}

	return nodes;
}