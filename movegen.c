/*
 * movegen.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include <stdbool.h>
#include "movegen.h"

u64 generateMoves(bool isWhite, Move moveList, int pos) {

	pos = genPushes(isWhite, moveList, pos);
	pos = genAttacks(isWhite, moveList, pos);
	pos = genSpecialMoves(isWhite, moveList, pos);

	return pos;
}

u64 generatePushes(bool isWhite, Move moveList, int pos) {

	pos = genKingPushes(isWhite, moveList, pos);
	pos = genQueenPushes(isWhite, moveList, pos);
	pos = genBishopPushes(isWhite, moveList, pos);
	pos = genKnightPushes(isWhite, moveList, pos);
	pos = genRookPushes(isWhite, moveList, pos);
	pos = genPawnPushes(isWhite, moveList, pos); /*only single push, double push is considered a special move */

	return pos;
}

u64 generateAttacks(bool isWhite, Move moveList, int pos) {

	pos = genKingAttacks(isWhite, moveList, pos);
	pos = genQueenAttacks(isWhite, moveList, pos);
	pos = genBishopAttacks(isWhite, moveList, pos);
	pos = genKnightAttacks(isWhite, moveList, pos);
	pos = genRookAttacks(isWhite, moveList, pos);
	pos = genPawnAttacks(isWhite, moveList, pos);

	return pos;
}

u64 generateSpecialMoves(bool isWhite, Move moveList, int pos) {

	pos = genDoublePushes(isWhite, moveList, pos);
	pos = genCastlingMoves(isWhite, moveList, pos);
	pos = genEnpassantMoves(isWhite, moveList, pos);
	pos = genPromotions(isWhite, moveList, pos);

	return pos;
}


/* pushes aka quiet moves */

u64 genKingPushes(bool isWhite, Move movelist, int pos) {
	
	if(isWhite) {
	} else {
	}

}

u64 genQueenPushes(bool is_white, Move move_list, int pos) {
	
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

				move.to = to;
				move.from = from;
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

				move.to = to;
				move.from = from;
				move.move_type = 0;

				move_list[pos++] = move;
			}
		}
	}
	
	return pos;
}
			



}





