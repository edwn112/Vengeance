/*
 * movegen.h
 *
 * Created on : May 3, 2017
 *     Author : Amar Thapa       
 */

#ifndef __MOVE_GEN_H__
#define __MOVE_GEN_H__

u64 gen_moves(bool is_white, Move move_list, int pos);

u64 gen_pushes(bool is_white, Move move_list, int pos);
u64 gen_attacks(bool is_white, Move move_list, int pos);
u64 gen_special_moves(bool is_white, Move move_list, int pos);

u64 gen_king_pushes(bool is_white, Move move_list, int pos);
u64 gen_queen_pushes(bool is_white, Move move_list, int pos);
u64 gen_bishop_pushes(bool is_white, Move move_list, int pos);
u64 gen_knight_pushes(bool is_white, Move move_list, int pos);
u64 gen_rook_pushes(bool is_white, Move move_list, int pos);
u64 gen_pawn_pushes(bool is_white, Move move_list, int pos);



#endif






