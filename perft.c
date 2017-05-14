#include <stdbool.h>
#include "perft.h"
#include "movegen.h"
#include "make_unmake.h"

u64 perft(u8 depth) {


	u32 move_list[MAX_MOVES];

	u64 nodes = 0;
	u8 n_moves, i;

	n_moves = gen_moves(move_list);


/*	printf("\n\n%u\n", n_moves);

	for (int i = 0; i < n_moves; ++i)
	{

		printf("%u - %u - %u, ", from_sq(move_list[i]), to_sq(move_list[i]), piece_type(move_list[i]));
	
	}
*/
	if(depth == 1)
		return n_moves;

	for(i = 0; i < n_moves; i++) {
		
		if(make_move(move_list[i]))
			nodes += perft(depth - 1);

		unmake_move(move_list[i]);
	}



	return nodes;
}