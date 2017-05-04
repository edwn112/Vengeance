/*
 * movegen.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include "globals.h"
#include "movegen.h"
#include "magicmoves.h"
#include "utility.h"

u64 gen_moves(bool is_white, u32 *move_list) {

	u8 pos = 0;

	pos = gen_pushes(is_white, move_list, pos);
	pos = gen_attacks(is_white, move_list, pos);
	pos = gen_special_moves(is_white, move_list, pos);

	return pos;
}

 u64 gen_pushes(bool is_white, u32 *move_list, u8 pos) {

	pos = gen_king_pushes(is_white, move_list, pos);
	pos = gen_queen_pushes(is_white, move_list, pos);
	pos = gen_bishop_pushes(is_white, move_list, pos);
	pos = gen_knight_pushes(is_white, move_list, pos);
	pos = gen_rook_pushes(is_white, move_list, pos);
	pos = gen_pawn_pushes(is_white, move_list, pos); /*only single push, double push is considered a special move */

	return pos;
}

u64 gen_attacks(bool is_white, u32 *move_list, u8 pos) {

	pos = gen_king_attacks(is_white, move_list, pos);
	pos = gen_queen_attacks(is_white, move_list, pos);
	pos = gen_bishop_attacks(is_white, move_list, pos);
	pos = gen_knight_attacks(is_white, move_list, pos);
	pos = gen_rook_attacks(is_white, move_list, pos);
	pos = gen_pawn_attacks(is_white, move_list, pos);

	return pos;
}

u64 gen_special_moves(bool is_white, u32 *move_list, u8 pos) {

	pos = gen_double_pushes(is_white, move_list, pos);
	pos = gen_castling_moves(is_white, move_list, pos);
	pos = gen_enpassant_moves(is_white, move_list, pos);
	pos = gen_promotions(is_white, move_list, pos);

	return pos;
}


/* pushes aka quiet moves */

u64 gen_king_pushes(bool is_white, u32 *move_list, u8 pos) {
	
	if(is_white) {
	} else {
	}

	return pos;
}

u64 gen_queen_pushes(bool is_white, u32 *move_list, u8 pos) {
	u64 queen_bb;

	if(is_white) {
		queen_bb = piece_bb[WHITE_QUEEN];
		
		while(queen_bb) {
			const u8 from = bit_scan_forward(queen_bb);
			queen_bb &= queen_bb - 1;
			
			u64 pushes = Qmagic(from, piece_bb[OCCUPIED]) & (~piece_bb[OCCUPIED]); 

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;

			}
		}
	} else {
		queen_bb = piece_bb[BLACK_QUEEN];

		while(queen_bb) {
			const u8 from = bit_scan_forward(queen_bb);
			queen_bb &= queen_bb - 1;

			u64 pushes = Qmagic(from, piece_bb[OCCUPIED]) & (~piece_bb[OCCUPIED]);

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;
			}
		}
	}
	
	return pos;
}

u64 gen_bishop_pushes(bool is_white, u32 *move_list, u8 pos) {
	u64 bishops_bb;

	if(is_white) {
		bishops_bb = piece_bb[WHITE_BISHOPS];
		
		while(bishops_bb) {
			const u8 from = bit_scan_forward(bishops_bb);
			bishops_bb &= bishops_bb - 1;
			
			u64 pushes = Qmagic(from, piece_bb[OCCUPIED]) & (~piece_bb[OCCUPIED]); 

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;

			}
		}
	} else {
		bishops_bb = piece_bb[BLACK_BISHOPS];

		while(bishops_bb) {
			const u8 from = bit_scan_forward(bishops_bb);
			bishops_bb &= bishops_bb - 1;

			u64 pushes = Bmagic(from, piece_bb[OCCUPIED]) & (~piece_bb[OCCUPIED]);

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;
			}
		}
	}
	
	return pos;
}

u64 gen_knight_pushes(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_rook_pushes(bool is_white, u32 *move_list, u8 pos) {
	u64 rooks_bb;

	if(is_white) {
		rooks_bb = piece_bb[WHITE_ROOKS];
		
		while(rooks_bb) {
			const u8 from = bit_scan_forward(rooks_bb);
			rooks_bb &= rooks_bb - 1;
			
			u64 pushes = Rmagic(from, piece_bb[OCCUPIED]) & (~piece_bb[OCCUPIED]); 

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;

			}
		}
	} else {
		rooks_bb = piece_bb[BLACK_ROOKS];

		while(rooks_bb) {
			const u8 from = bit_scan_forward(rooks_bb);
			rooks_bb &= rooks_bb - 1;

			u64 pushes = Rmagic(from, piece_bb[OCCUPIED]) & (~piece_bb[OCCUPIED]);

			while(pushes) {
				const u8 to = bit_scan_forward(pushes);
				pushes &= pushes - 1;
			}
		}
	}
	
	return pos;
}

u64 gen_pawn_pushes(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

/* attacks */

u64 gen_king_attacks(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_queen_attacks(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_bishop_attacks(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_knight_attacks(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_rook_attacks(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_pawn_attacks(bool is_white, u32 *move_list, u8 pos) {
	return pos;
}

/* special moves */

u64 gen_double_pushes(bool is_white, u32 *move_list, u8 pos) {

	return pos;
}

u64 gen_castling_moves(bool is_white, u32 *move_list, u8 pos) {

	return pos;
}

u64 gen_enpassant_moves(bool is_white, u32 *move_list, u8 pos) {

	return pos;
}

u64 gen_promotions(bool is_white, u32 *move_list, u8 pos) {

	return pos;
}








