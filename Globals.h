/*
 * Globals.h
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdbool.h>
#include <stdio.h>

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;

#define C64(constantU64) constantU64

#define MAX_MOVES 256

#define COLOR 1 /* 0 for white, COLOR ^ 1 = 1 for black */ 

/* pieceBB is an array containing bitboards for all pieces */

u64 piece_bb[2][7]; /* color * (piece_type + pieces of that color) = 2 * 7 = 14 */

/* array size for indexBB array */
#define INDEX_BB_SIZE 64

u64 index_bb[INDEX_BB_SIZE];

/********************************/

#define MAX_PLY 1024
u32 ply;

struct hist {
	u64 move;
	u64 ep_sq;
	u8 castle_flags;
	u8 ep_flag;
} hist[MAX_PLY];

/********************************/

/* index for pieces in pieceBB array */

#define KING 0
#define QUEEN 1
#define BISHOPS 2
#define KNIGHTS 3
#define ROOKS 4
#define PAWNS 5
#define PIECES 6

/* occupied and empty squares bb */

u64 occupied, empty;

/* Extract data from a move structure */
#define promotion_type(move)    (((00000000011000000000000000000000 & move) >> 23))
#define castle_dir(move)		(((00000000000110000000000000000000 & move) >> 21))
#define move_type(move)         (((00000000000001110000000000000000 & move) >> 19))
#define color(move)             (((00000000000000001110000000000000 & move) >> 16))
#define c_piece(move)           (((00000000000000111000000000000000 & move) >> 15))
#define piece(move)	            (((00000000000000000111000000000000 & move) >> 12)) 	
#define from_sq(move)              (((00000000000000000000111111000000 & move) >> 6))
#define to_sq(move)                (( 00000000000000000000000000111111 & move))

#define RANK_2 0x000000000000FF00U
#define RANK_7 0x00FF000000000000U



#endif /* GLOBALS_H_ */
