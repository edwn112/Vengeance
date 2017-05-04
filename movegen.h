/*
 * movegen.h
 *
 * Created on : May 3, 2017
 *     Author : Amar Thapa       
 */

#ifndef __MOVE_GEN_H__
#define __MOVE_GEN_H__


u64 gen_moves(bool is_white, u32 *move_list);

inline u64 gen_pushes(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_attacks(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_special_moves(bool is_white, u32 *move_list, u8 pos);

inline u64 gen_king_pushes(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_queen_pushes(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_bishop_pushes(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_knight_pushes(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_rook_pushes(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_pawn_pushes(bool is_white, u32 *move_list, u8 pos);


inline u64 gen_king_attacks(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_queen_attacks(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_bishop_attacks(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_knight_attacks(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_rook_attacks(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_pawn_attacks(bool is_white, u32 *move_list, u8 pos);

inline u64 gen_double_pushes(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_castling_moves(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_enpassant_moves(bool is_white, u32 *move_list, u8 pos);
inline u64 gen_promotions(bool is_white, u32 *move_list, u8 pos);

#endif






