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

/* array size for pieceBB array */

#define PIECE_BB_SIZE 16
#define INDEX_BB_SIZE 64

/* pieceBB is an array containing bitboards for all pieces */

u64 piece_bb[PIECE_BB_SIZE];
u64 index_bb[INDEX_BB_SIZE];

/* index for white pieces in pieceBB array */

#define WHITE_KING 0
#define WHITE_QUEEN 1
#define WHITE_BISHOPS 2
#define WHITE_KNIGHTS 3
#define WHITE_ROOKS 4
#define WHITE_PAWNS 5
#define WHITE_PIECES 6

/* index for black pieces in pieceBB array */

#define BLACK_KING 7
#define BLACK_QUEEN 8
#define BLACK_BISHOPS 9
#define BLACK_KNIGHTS 10
#define BLACK_ROOKS 11
#define BLACK_PAWNS 12
#define BLACK_PIECES 13

/* index for occupied and empty squares in pieceBB array */

#define OCCUPIED 14
#define EMPTY 15

#endif /* GLOBALS_H_ */
