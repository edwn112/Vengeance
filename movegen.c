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

			move_list[pos++] = create_move(0, 0, 0, COLOR ^ 1, 7, KING, from, to);
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
	u64 king_bb = piece_bb[COLOR ^ 1][KING];

	while(king_bb) {
		const u8 from = bit_scan_forward(king_bb);
		king_bb &= king_bb - 1;

		u64 moves = get_king_attacks(from) & (~piece_bb[COLOR ^ 1][PIECES]);
		u64 attacks = moves & piece_bb[COLOR][PIECES];

		while(attacks) {
			const u8 to = bit_scan_forward(attacks);
			attacks &= attacks - 1;

			if(to & piece_bb[COLOR][QUEEN]) {
				move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, QUEEN, KING, from, to); 
			} else if(piece_bb[COLOR][BISHOPS]) {
				u64 bishops_bb = piece_bb[COLOR][BISHOPS];
				while(bishops_bb) {
					const u8 sq = bit_scan_forward(bishops_bb);
					bishops_bb &= bishops_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, BISHOPS, KING, from, to);
				}
			} else if(piece_bb[COLOR][KNIGHTS]) {
				u64 knights_bb = piece_bb[COLOR][KNIGHTS];
				while(knights_bb) {
					const u8 sq = bit_scan_forward(knights_bb);
					knights_bb &= knights_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, KNIGHTS, KING, from, to);
				}
			} else if(piece_bb[COLOR][ROOKS]) {
				u64 rooks_bb = piece_bb[COLOR][ROOKS];
				while(rooks_bb) {
					const u8 sq = bit_scan_forward(rooks_bb);
					rooks_bb &= rooks_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, ROOKS, KING, from, to);
				}
			} else if(piece_bb[COLOR][PAWNS]) {
				u64 pawns_bb = piece_bb[COLOR][PAWNS];
				while(pawns_bb) {
					const u8 sq = bit_scan_forward(pawns_bb);
					pawns_bb &= pawns_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, PAWNS, KING, from, to);
				}
			}

		}
	}

	return pos;
}

u64 gen_queen_attacks(u32 *move_list, u8 pos) {
	u64 queen_bb = piece_bb[COLOR ^ 1][QUEEN];

	while(queen_bb) {
		const u8 from = bit_scan_forward(queen_bb);
		queen_bb &= queen_bb - 1;
		
		u64 moves = Qmagic(from, occupied) & (~piece_bb[COLOR ^ 1][PIECES]); 
		u64 attacks = moves & piece_bb[COLOR][PIECES];

		while(attacks) {
			const u8 to = bit_scan_forward(attacks);
			attacks &= attacks - 1;

			if(to & piece_bb[COLOR][QUEEN]) {
				move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, QUEEN, QUEEN, from, to); 
			} else if(piece_bb[COLOR][BISHOPS]) {
				u64 bishops_bb = piece_bb[COLOR][BISHOPS];
				while(bishops_bb) {
					const u8 sq = bit_scan_forward(bishops_bb);
					bishops_bb &= bishops_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, BISHOPS, QUEEN, from, to);
				}
			} else if(piece_bb[COLOR][KNIGHTS]) {
				u64 knights_bb = piece_bb[COLOR][KNIGHTS];
				while(knights_bb) {
					const u8 sq = bit_scan_forward(knights_bb);
					knights_bb &= knights_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, KNIGHTS, QUEEN, from, to);
				}
			} else if(piece_bb[COLOR][ROOKS]) {
				u64 rooks_bb = piece_bb[COLOR][ROOKS];
				while(rooks_bb) {
					const u8 sq = bit_scan_forward(rooks_bb);
					rooks_bb &= rooks_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, ROOKS, QUEEN, from, to);
				}
			} else if(piece_bb[COLOR][PAWNS]) {
				u64 pawns_bb = piece_bb[COLOR][PAWNS];
				while(pawns_bb) {
					const u8 sq = bit_scan_forward(pawns_bb);
					pawns_bb &= pawns_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, PAWNS, QUEEN, from, to);
				}
			}
		}
	}

	return pos;
}

u64 gen_bishop_attacks(u32 *move_list, u8 pos) {
	u64 bishop_bb = piece_bb[COLOR ^ 1][BISHOPS];

	while(bishop_bb) {
		const u8 from = bit_scan_forward(bishop_bb);
		bishop_bb &= bishop_bb - 1;
		
		u64 moves = Bmagic(from, occupied) & (~piece_bb[COLOR ^ 1][PIECES]); 
		u64 attacks = moves & piece_bb[COLOR][PIECES];

		while(attacks) {
			const u8 to = bit_scan_forward(attacks);
			attacks &= attacks - 1;

			if(to & piece_bb[COLOR][QUEEN]) {
				move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, QUEEN, BISHOPS, from, to); 
			} else if(piece_bb[COLOR][BISHOPS]) {
				u64 bishops_bb = piece_bb[COLOR][BISHOPS];
				while(bishops_bb) {
					const u8 sq = bit_scan_forward(bishops_bb);
					bishops_bb &= bishops_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, BISHOPS, BISHOPS, from, to);
				}
			} else if(piece_bb[COLOR][KNIGHTS]) {
				u64 knights_bb = piece_bb[COLOR][KNIGHTS];
				while(knights_bb) {
					const u8 sq = bit_scan_forward(knights_bb);
					knights_bb &= knights_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, KNIGHTS, BISHOPS, from, to);
				}
			} else if(piece_bb[COLOR][ROOKS]) {
				u64 rooks_bb = piece_bb[COLOR][ROOKS];
				while(rooks_bb) {
					const u8 sq = bit_scan_forward(rooks_bb);
					rooks_bb &= rooks_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, ROOKS, BISHOPS, from, to);
				}
			} else if(piece_bb[COLOR][PAWNS]) {
				u64 pawns_bb = piece_bb[COLOR][PAWNS];
				while(pawns_bb) {
					const u8 sq = bit_scan_forward(pawns_bb);
					pawns_bb &= pawns_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, PAWNS, BISHOPS, from, to);
				}
			}
		}
	}

	return pos;
}

u64 gen_knight_attacks(u32 *move_list, u8 pos) {
	
	u64 knights_bb = piece_bb[COLOR ^ 1][KNIGHTS];

	while(knights_bb) {
		const u8 from = bit_scan_forward(knights_bb);
		knights_bb &= knights_bb - 1;

		u64 moves = get_knight_attacks(from) & (~piece_bb[COLOR ^ 1][PIECES]);
		u64 attacks = moves & piece_bb[COLOR][PIECES];

		while (attacks) {
			const u8 to = bit_scan_forward(attacks);
			attacks &= attacks - 1;

		}
	}

	return pos;
}

u64 gen_rook_attacks(u32 *move_list, u8 pos) {
	u64 rooks_bb = piece_bb[COLOR ^ 1][ROOKS];

	while(rooks_bb) {
		const u8 from = bit_scan_forward(rooks_bb);
		rooks_bb &= rooks_bb - 1;
		
		u64 moves = Rmagic(from, occupied) & (~piece_bb[COLOR ^ 1][PIECES]); 
		u64 attacks = moves & piece_bb[COLOR][PIECES];

		while(attacks) {
			const u8 to = bit_scan_forward(attacks);
			attacks &= attacks - 1;

			if(to & piece_bb[COLOR][QUEEN]) {
				move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, QUEEN, ROOKS, from, to); 
			} else if(piece_bb[COLOR][BISHOPS]) {
				u64 bishops_bb = piece_bb[COLOR][BISHOPS];
				while(bishops_bb) {
					const u8 sq = bit_scan_forward(bishops_bb);
					bishops_bb &= bishops_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, BISHOPS, ROOKS, from, to);
				}
			} else if(piece_bb[COLOR][KNIGHTS]) {
				u64 knights_bb = piece_bb[COLOR][KNIGHTS];
				while(knights_bb) {
					const u8 sq = bit_scan_forward(knights_bb);
					knights_bb &= knights_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, KNIGHTS, ROOKS, from, to);
				}
			} else if(piece_bb[COLOR][ROOKS]) {
				u64 rooks_bb = piece_bb[COLOR][ROOKS];
				while(rooks_bb) {
					const u8 sq = bit_scan_forward(rooks_bb);
					rooks_bb &= rooks_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, ROOKS, ROOKS, from, to);
				}
			} else if(piece_bb[COLOR][PAWNS]) {
				u64 pawns_bb = piece_bb[COLOR][PAWNS];
				while(pawns_bb) {
					const u8 sq = bit_scan_forward(pawns_bb);
					pawns_bb &= pawns_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, PAWNS, ROOKS, from, to);
				}
			}
		}
	}

	return pos;
}

u64 gen_pawn_attacks(u32 *move_list, u8 pos) {
	u64 pawns_bb = piece_bb[COLOR ^ 1][PAWNS];

	while(pawns_bb) {
		const u8 from = bit_scan_forward(pawns_bb);
		pawns_bb &= pawns_bb - 1;

		u64 attacks = ((index_bb[from] << 7) >> 14 * (COLOR ^ 1)) | ((index_bb[from] << 9) >> 16 * (COLOR ^ 1));

		while(attacks) {
			const u8 to = bit_scan_forward(attacks);
			attacks &= attacks - 1;

			if(to & piece_bb[COLOR][QUEEN]) {
				move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, QUEEN, PAWNS, from, to); 
			} else if(piece_bb[COLOR][BISHOPS]) {
				u64 bishops_bb = piece_bb[COLOR][BISHOPS];
				while(bishops_bb) {
					const u8 sq = bit_scan_forward(bishops_bb);
					bishops_bb &= bishops_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, BISHOPS, PAWNS, from, to);
				}
			} else if(piece_bb[COLOR][KNIGHTS]) {
				u64 knights_bb = piece_bb[COLOR][KNIGHTS];
				while(knights_bb) {
					const u8 sq = bit_scan_forward(knights_bb);
					knights_bb &= knights_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, KNIGHTS, PAWNS, from, to);
				}
			} else if(piece_bb[COLOR][ROOKS]) {
				u64 rooks_bb = piece_bb[COLOR][ROOKS];
				while(rooks_bb) {
					const u8 sq = bit_scan_forward(rooks_bb);
					rooks_bb &= rooks_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, ROOKS, PAWNS, from, to);
				}
			} else if(piece_bb[COLOR][PAWNS]) {
				u64 pawns_bb = piece_bb[COLOR][PAWNS];
				while(pawns_bb) {
					const u8 sq = bit_scan_forward(pawns_bb);
					pawns_bb &= pawns_bb - 1;

					if(sq == to)
						move_list[pos++] = create_move(0, 0, 1, COLOR ^ 1, PAWNS, PAWNS, from, to);
				}
			}
		}
	}


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

	if(COLOR ^ 1) {
		
		if(castling_rights[1]) {
	
			if(hist[ply].castle_flags & 0x0100) {
				u64 bq_sqs = empty & BQ_SIDE_SQS;


				if(bq_sqs == BQ_SIDE_SQS) {
					u32 move = create_move(0, 2, 4, 1, ROOKS, KING, 60, 58);
					move_list[pos++] = move;
				}
			
			} else if (hist[ply].castle_flags & 0x1000) {
		
				u64 bk_sqs = empty & BK_SIDE_SQS;

				if(bk_sqs == BK_SIDE_SQS) {
					u32 move = create_move(0, 3, 4, 1, ROOKS, KING, 60, 62);
					move_list[pos++] = move;
				}
			}
		}
	} else {

		if(castling_rights[0]) {
			if(hist[ply].castle_flags & 0x0001) {
				u64 wq_sqs = empty & WQ_SIDE_SQS;

				if(wq_sqs == WQ_SIDE_SQS) {
					u32 move = create_move(0, 0, 4, 0, ROOKS, KING, 4, 2); 
					move_list[pos++] = move;
				}
			} else if(hist[ply].castle_flags & 0x0010) {
				u64 wk_sqs = empty & WK_SIDE_SQS;

				if(wk_sqs == WK_SIDE_SQS) {
					u32 move = create_move(0, 1, 4, 0, ROOKS, KING, 4, 6);
					move_list[pos++] = move;
				}
			}	
		}
	}

	return pos;
}

u64 gen_enpassant_moves(u32 *move_list, u8 pos) {

	if(hist[ply].ep_flag) {
		hist[ply].ep_flag ^= 1;

		u64 ep_sq = hist[ply].ep_sq;	
		u64 target_sqs = ((ep_sq >> 7) << (14 * COLOR ^ 1)) | ((ep_sq >> 7) << (16 * COLOR ^ 1));
		u64 target_pawns = target_sqs & piece_bb[COLOR ^ 1][PAWNS];

		while(target_pawns) {
			const u8 from = bit_scan_forward(target_pawns);
			target_pawns &= target_pawns - 1;

			const u8 to = ep_sq;
			u32 move = create_move(0, 0, 3, COLOR ^ 1, PAWNS, PAWNS, from, to);
			move_list[pos++] = move;
		}
	}

	return pos;
}

u64 gen_promotions(u32 *move_list, u8 pos) {
	u64 prom_pawns = piece_bb[COLOR ^ 1][PAWNS];

	if(COLOR ^ 1) {
		prom_pawns &= RANK_2;
	}else {
		prom_pawns &= RANK_7;
	}

	while(prom_pawns) {

		const u8 from = bit_scan_forward(prom_pawns);
		prom_pawns &= prom_pawns - 1;

		u8 to_attack = (from << 7) >> (14 * (COLOR ^ 1)) | (from << 9) >> (16 * (COLOR ^ 1));

		while(to_attack) {
			const u8 to = bit_scan_forward(to_attack);
			to_attack &= to_attack - 1;

			if(to & piece_bb[COLOR][QUEEN]) {
				u64 queen_prom = create_move(0, 0, 5, COLOR ^ 1, QUEEN, PAWNS, from, to);
				u64 rook_prom = create_move(1, 0, 5, COLOR ^ 1, QUEEN, PAWNS, from, to);
				u64 knight_prom = create_move(2, 0, 5, COLOR ^ 1, QUEEN, PAWNS, from, to);
				u64 bishop_prom = create_move(3, 0, 5, COLOR ^ 1, QUEEN, PAWNS, from, to);		
			
				move_list[pos++] = queen_prom;
				move_list[pos++] = rook_prom;
				move_list[pos++] = knight_prom;
				move_list[pos++] = bishop_prom; 
			} else if(piece_bb[COLOR][BISHOPS]) {
				u64 bishops_bb = piece_bb[COLOR][BISHOPS];
				while(bishops_bb) {
					const u8 sq = bit_scan_forward(bishops_bb);
					bishops_bb &= bishops_bb - 1;

					if(sq == to){
						u64 queen_prom = create_move(0, 0, 5, COLOR ^ 1, BISHOPS, PAWNS, from, to);
						u64 rook_prom = create_move(1, 0, 5, COLOR ^ 1, BISHOPS, PAWNS, from, to);
						u64 knight_prom = create_move(2, 0, 5, COLOR ^ 1, BISHOPS, PAWNS, from, to);
						u64 bishop_prom = create_move(3, 0, 5, COLOR ^ 1, BISHOPS, PAWNS, from, to);		
					
						move_list[pos++] = queen_prom;
						move_list[pos++] = rook_prom;
						move_list[pos++] = knight_prom;
						move_list[pos++] = bishop_prom;
					}
				}
			} else if(piece_bb[COLOR][KNIGHTS]) {
				u64 knights_bb = piece_bb[COLOR][KNIGHTS];
				while(knights_bb) {
					const u8 sq = bit_scan_forward(knights_bb);
					knights_bb &= knights_bb - 1;

					if(sq == to){
						u64 queen_prom = create_move(0, 0, 5, COLOR ^ 1, KNIGHTS, PAWNS, from, to);
						u64 rook_prom = create_move(1, 0, 5, COLOR ^ 1, KNIGHTS, PAWNS, from, to);
						u64 knight_prom = create_move(2, 0, 5, COLOR ^ 1, KNIGHTS, PAWNS, from, to);
						u64 bishop_prom = create_move(3, 0, 5, COLOR ^ 1, KNIGHTS, PAWNS, from, to);		
					
						move_list[pos++] = queen_prom;
						move_list[pos++] = rook_prom;
						move_list[pos++] = knight_prom;
						move_list[pos++] = bishop_prom;
					}
				}
			} else if(piece_bb[COLOR][ROOKS]) {
				u64 rooks_bb = piece_bb[COLOR][ROOKS];
				while(rooks_bb) {
					const u8 sq = bit_scan_forward(rooks_bb);
					rooks_bb &= rooks_bb - 1;

					if(sq == to){
						u64 queen_prom = create_move(0, 0, 5, COLOR ^ 1, ROOKS, PAWNS, from, to);
						u64 rook_prom = create_move(1, 0, 5, COLOR ^ 1, ROOKS, PAWNS, from, to);
						u64 knight_prom = create_move(2, 0, 5, COLOR ^ 1, ROOKS, PAWNS, from, to);
						u64 bishop_prom = create_move(3, 0, 5, COLOR ^ 1, ROOKS, PAWNS, from, to);		
					
						move_list[pos++] = queen_prom;
						move_list[pos++] = rook_prom;
						move_list[pos++] = knight_prom;
						move_list[pos++] = bishop_prom;
					}
				}
			}	
		}

		u8 to_push = (from << 8) >> (16 * (COLOR ^ 1)) & empty;

		while(to_push) {
			const u8 to = bit_scan_forward(to_push);
			to_push &= to_push - 1;
			
			u64 queen_prom = create_move(0, 0, 5, COLOR ^ 1, DUMMY, PAWNS, from, to);
			u64 rook_prom = create_move(1, 0, 5, COLOR ^ 1, DUMMY, PAWNS, from, to);
			u64 knight_prom = create_move(2, 0, 5, COLOR ^ 1, DUMMY, PAWNS, from, to);
			u64 bishop_prom = create_move(3, 0, 5, COLOR ^ 1, DUMMY, PAWNS, from, to);		
		
			move_list[pos++] = queen_prom;
			move_list[pos++] = rook_prom;
			move_list[pos++] = knight_prom;
			move_list[pos++] = bishop_prom;
		} 
	}

	return pos;
}

/*
*	Move Type
*
*	0 -> quiet moves
*	1 -> captures
*	2 -> pawn double moves
*	3 -> en passant
*	4 -> castling
*	5 -> promotions
*	6 -> king moves
*/

/*
*	Prom Type
*
*	0 - Queen	
*	1 - Rook
*	2 - Knight
*	3 - Bishop
**/

u32 create_move(u8 promotion_type, u8 castle_dir, u8 move_type, u8 color, u8 c_piece, u8 piece, u8 from, u8 to) {
	
	return (0ull | (u32) promotion_type << 24 | (u32) castle_dir << 22 | (u32) move_type << 19 |
	 (u32) color << 18 | (u32) c_piece << 15 | (u32) piece << 12 | (u32) from << 6 | (u32) to);
}







