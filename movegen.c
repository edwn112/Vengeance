/*
 * movegen.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include "globals.h"
#include "movegen.h"
#include "magicmoves.h"
#include "nonslidingmoves.h"
#include "utility.h"

u64 gen_moves(u32 *move_list) {

	printf("For side ");
	if(COLOR ^ 1)
		printf(" - BLACK\n");
	else
		printf(" - WHITE\n");
	
	u8 pos = 0;

	pos = gen_pushes(move_list, pos);
	pos = gen_attacks(move_list, pos);
	pos = gen_special_moves(move_list, pos);

	return pos;
}

 u64 gen_pushes(u32 *move_list, u8 pos) {

	pos = gen_king_pushes(move_list, pos);
	pos = gen_queen_pushes(move_list, pos);
	pos = gen_bishop_pushes(move_list, pos);
	pos = gen_knight_pushes(move_list, pos);
	pos = gen_rook_pushes(move_list, pos);
	pos = gen_pawn_pushes(move_list, pos); /*only single push, double push is considered a special move */

	return pos;
}

u64 gen_attacks(u32 *move_list, u8 pos) {

	pos = gen_king_attacks(move_list, pos);
	pos = gen_queen_attacks(move_list, pos);
	pos = gen_bishop_attacks(move_list, pos);
	pos = gen_knight_attacks(move_list, pos);
	pos = gen_rook_attacks(move_list, pos);
	pos = gen_pawn_attacks(move_list, pos);

	return pos;
}

u64 gen_special_moves(u32 *move_list, u8 pos) {

	pos = gen_double_pushes(move_list, pos);
	pos = gen_castling_moves(move_list, pos);
	pos = gen_enpassant_moves(move_list, pos);
	pos = gen_promotions(move_list, pos);

	return pos;
}


/* pushes aka quiet moves */

u64 gen_king_pushes(u32 *move_list, u8 pos) {

	u64 king_bb = piece_bb[COLOR ^ 1][KING];

	while(king_bb) {
		const u8 from = bit_scan_forward(king_bb);
		king_bb &= king_bb - 1;

		u64 pushes  = get_king_attacks(from) & (~occupied);

		while(pushes) {
			const u8 to = bit_scan_forward(pushes);
			pushes &= pushes - 1;

			move_list[pos++] = create_move(0, 0, 6, COLOR ^ 1, 7, KING, from, to);
		}
	}

	return pos;
}

u64 gen_queen_pushes(u32 *move_list, u8 pos) {
	
	u64 queen_bb = piece_bb[COLOR ^ 1][QUEEN];

	while(queen_bb) {
		const u8 from = bit_scan_forward(queen_bb);
		queen_bb &= queen_bb - 1;
		
		u64 pushes = Qmagic(from, occupied) & (~occupied); 
	
		while(pushes) {
			const u8 to = bit_scan_forward(pushes);
			pushes &= pushes - 1;

			move_list[pos++] = create_move(0, 0, 0, COLOR ^ 1, 7, QUEEN, from, to); /* 7 is a dummy value indicating no captured piece */
		}
	}

	return pos;
}

u64 gen_bishop_pushes(u32 *move_list, u8 pos) {
	u64 bishops_bb = piece_bb[COLOR ^ 1][BISHOPS];
			
	while(bishops_bb) {
		const u8 from = bit_scan_forward(bishops_bb);
		bishops_bb &= bishops_bb - 1;
		
		u64 pushes = Bmagic(from, occupied) & (~occupied); 
	
		while(pushes) {
			const u8 to = bit_scan_forward(pushes);
			pushes &= pushes - 1;
	
			move_list[pos++] = create_move(0, 0, 0, COLOR ^ 1, 7, BISHOPS, from, to); /* 7 is a dummy value indicating no captured piece */
		}
	}

	return pos;
}

u64 gen_knight_pushes(u32 *move_list, u8 pos) {

	u64 knights_bb = piece_bb[COLOR ^ 1][KNIGHTS];

	while(knights_bb) {
		const u8 from = bit_scan_forward(knights_bb);
		knights_bb &= knights_bb - 1;

		u64 pushes = get_knight_attacks(from) & (~occupied);

		while (pushes) {
			const u8 to = bit_scan_forward(pushes);
			pushes &= pushes - 1;

			move_list[pos++] = create_move(0, 0, 0, COLOR ^ 1, 7, KNIGHTS, from, to);
		}
	}

	return pos;
}

u64 gen_rook_pushes(u32 *move_list, u8 pos) {
	u64 rooks_bb = piece_bb[COLOR ^ 1][ROOKS];
		
	while(rooks_bb) {
		const u8 from = bit_scan_forward(rooks_bb);
		rooks_bb &= rooks_bb - 1;
		
		u64 pushes = Rmagic(from, occupied) & (~occupied); 
	
		while(pushes) {
			const u8 to = bit_scan_forward(pushes);
			pushes &= pushes - 1;

			move_list[pos++] = create_move(0, 0, 0, 0, 7, ROOKS, from, to); /* 7 is a dummy value indicating no captured piece */
		}
	}

	return pos;
}

u64 gen_pawn_pushes(u32 *move_list, u8 pos) {
	u64 pawns_bb = piece_bb[COLOR ^ 1][PAWNS];
	u64 pawns_single_push_target_squares = ((pawns_bb << 8) >> 16 * (COLOR ^ 1)) & empty;

	while(pawns_single_push_target_squares) {
		const u8 to = bit_scan_forward(pawns_single_push_target_squares);
		pawns_single_push_target_squares &= pawns_single_push_target_squares - 1;

		u8 from;

		if(COLOR)
			from = to << 8;
		else
			from = to >> 8;

		move_list[pos++] = create_move(0, 0, 0, COLOR ^ 1, 7, 5, from, to);

	}

	return pos;
}



/* attacks */

u64 gen_king_attacks(u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_queen_attacks(u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_bishop_attacks(u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_knight_attacks(u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_rook_attacks(u32 *move_list, u8 pos) {
	return pos;
}

u64 gen_pawn_attacks(u32 *move_list, u8 pos) {
	return pos;
}

/* special moves */

u64 gen_double_pushes(u32 *move_list, u8 pos) {
	
	u64 pawns_bb = piece_bb[COLOR ^ 1][PAWNS];
	
	if(COLOR ^ 1) 
		pawns_bb &= RANK_7;
	else 
		pawns_bb &= RANK_2;

	u64 pawns_single_push = ((pawns_bb << 8) >> 16 * (COLOR ^ 1));

	u64 pawns_double_push_target_squares = ((pawns_single_push << 8) 
		>> (16 * (COLOR ^ 1))) & empty;

	while(pawns_double_push_target_squares) {
		const u8 to = bit_scan_forward(pawns_double_push_target_squares);
		pawns_double_push_target_squares &= pawns_double_push_target_squares - 1;

		u8 from;

		if(COLOR)
			from = to << 16;
		else
			from = to >> 16;

		move_list[pos++] = create_move(0, 0, 2, COLOR ^ 1, 7, 5, from, to);

	}

	return pos;
}

u64 gen_castling_moves(u32 *move_list, u8 pos) {

	return pos;
}

u64 gen_enpassant_moves(u32 *move_list, u8 pos) {

	return pos;
}

u64 gen_promotions(u32 *move_list, u8 pos) {

	return pos;
}








