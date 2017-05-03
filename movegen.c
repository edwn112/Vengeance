/*
 * movegen.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include <stdbool.h>
#include "globals.h"
#include "movegen.h"

u64 gen_moves(bool is_white, Move move_list, int pos) {

	pos = gen_pushes(is_white, move_list, pos);
	pos = gen_attacks(is_white, move_list, pos);
	pos = gen_special_moves(is_white, move_list, pos);

	return pos;
}

u64 gen_pushes(bool is_white, Move move_list, int pos) {

	pos = gen_king_pushes(is_white, move_list, pos);
	pos = gen_queen_pushes(is_white, move_list, pos);
	pos = gen_bishop_pushes(is_white, move_list, pos);
	pos = gen_knight_pushes(is_white, move_list, pos);
	pos = gen_rook_pushes(is_white, move_list, pos);
	pos = gen_pawn_pushes(is_white, move_list, pos); /*only single push, double push is considered a special move */

	return pos;
}

u64 gen_attacks(bool is_white, Move move_list, int pos) {

	pos = gen_king_attacks(is_white, move_list, pos);
	pos = gen_queen_attacks(is_white, move_list, pos);
	pos = gen_bishop_attacks(is_white, move_list, pos);
	pos = gen_knight_attacks(is_white, move_list, pos);
	pos = gen_rook_attacks(is_white, move_list, pos);
	pos = gen_pawn_attacks(is_white, move_list, pos);

	return pos;
}

u64 gen_special_moves(bool isWhite, Move move_list, int pos) {

	pos = gen_double_pushes(is_white, move_list, pos);
	pos = gen_castling_moves(is_white, move_list, pos);
	pos = gen_enpassant_moves(is_white, move_list, pos);
	pos = gen_promotions(is_white, move_list, pos);

	return pos;
}


/* pushes aka quiet moves */

u64 gen_king_pushes(bool is_white, Move move_list, int pos) {
	
	if(is_white) {
	} else {
	}

}

u64 gen_queen_pushes(bool is_white, Move move_list, int pos) {
	
	Move move;
	u64 queen_bb;

	if(is_white) {
		queen_bb = piece_bb[WHITE_QUEEN];
		
		while(queen_bb) {
			const u8 from = bit_scan_forward(queen_bb);
			queen_bb &= queen_bb - 1;
			
			u64 pushes = Qmagic(from, piece_bb[ALL]) & (~piece_bb[ALL]); 
		
			move.piece = WHITE_QUEEN;
			move.color = WHITE_PIECES;

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;

				move.to = index_bb[to];
				move.from = index_bb[from];
				move.movetype = 0;

				move_list[pos++] = move;
			}
		}
	} else {
		queen_bb = piece_bb[BLACK_QUEEN];

		while(queenBB) {
			const u8 from = bit_scan_forward(queen_bb);
			queen_bb &= queen_bb - 1;

			u64 pushes = Qmagic(from, piece_bb[ALL]) & (~piece_bb[ALL]);

			move.piece = BLACK_QUEEN;
			move.color = BLACK_PIECES;

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;

				move.to = index_bb[to];
				move.from = index_bb[from];
				move.move_type = 0;

				move_list[pos++] = move;
			}
		}
	}
	
	return pos;
}

u64 generate_bishop_pushes(bool is_white, Move move_list, int pos) {
	return pos;
}

u64 generate_knight_pushes(bool is_white, Move move_list, int pos) {
	return pos;
}

u64 generate_rook_pushes(bool is_white, Move move_list, int pos) {
	return pos;
}

u64 generate_pawn_pushes(bool is_white, Move move_list, int pos) {
	return pos;
}





			



}





