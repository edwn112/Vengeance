#include <stdbool.h>
#include "perft.h"
#include "movegen.h"
#include "make_unmake.h"
#include "utility.h"


u64 perft(u8 depth, u8 Color) {

	u32 move_list[MAX_MOVES];

	u64 nodes = 0;
	u8 n_moves, i;

	if(depth == 0) {
		return 1;
	}

	color = Color;

	n_moves = gen_moves(move_list, color);
	
	for(i = 0; i < n_moves; i++) {
		ply = ply + 1;
		
		make_move(move_list[i]);
		if(!is_sq_attacked((bit_scan_forward(piece_bb[color][KING])), color)) { 
			
			u32 move = move_list[i];
			hist_add.move = move;
			//hist_add.ep_sq = hist[ply - 1].ep_sq;
			//hist_add.ep_flag = hist[ply - 1].ep_flag;
			//hist_add.castle_flags = hist[ply - 1].castle_flags;  

			hist[ply] = hist_add;

			switch(move_type(move)) {
				/*case KING:
					printf("K%lu - K%lu \n", from_sq(move), to_sq(move));
					break;
				case QUEEN:
					printf("Q%lu - Q%lu \n", from_sq(move), to_sq(move));
					break;
				case BISHOPS:
					printf("b%lu - b%lu \n", from_sq(move), to_sq(move));
					break;
				case KNIGHTS:
					printf("n%lu - n%lu \n", from_sq(move), to_sq(move));
					break;
				*/
/*
				case 1:
					if(piece_type(move) == KNIGHTS && color == BLACK) {
						printf("n%lu - n%lu, ", from_sq(move), to_sq(move));
						printf("%lu    ", c_piece_type(move));
					}
					break;
				
				/*case PAWNS:
					printf("p%lu - p%lu \n", from_sq(move), to_sq(move));
					break;
				*/
				//Sleep(200);
			}

			nodes += perft(depth - 1, color ^ 1);	

		}
	
		unmake_move(move_list[i]);
		ply = ply - 1;
	}

	return nodes;
}