#include "make_unmake.h"

void make_move(u32 move) {
	struct hist hist_add;
	u64 from, to;

	switch(move_type(move)) {
		case 0 : break;
		case 1 : break;
		case 2 : 
					from = index_bb[from_sq(move)];
					to = index_bb[to_sq(move)];

					hist_add.move = move;
					hist_add.ep_sq = (from << 8) >> 16 * color(move);
					hist_add.ep_flag = 1;

					hist[++ply] = hist_add;

				 break;
		case 3 : break;
		case 4 : break;
		case 5 : break;
	}

}

void unmake_move() {

	struct hist fetch_hist;
	
	fetch_hist = hist[ply];

	u32 move = fetch_hist.move;

	switch(move_type(move)) {
		case 0 : break;
		case 1 : break;
		case 2 : break;
		case 3 : break;
		case 4 : break;
		case 5 : break;
	}
}