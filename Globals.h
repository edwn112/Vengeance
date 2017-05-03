/*
 * Globals.h
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;

/* structure to hold a move */

struct Move {
	int to;        /* to square of a move */
	int from;	   /* from square of a move */
	int movetype;  /* 0-pushes, 1-captures, 2-castling, 3-enPassant, 4-promotions, 5-doubleMoves */
	int piece;     /* the piece to move */
	int color;     /* side to which piece belongs i.e bb containing all pieces of that color*/
	int cpiece;    /* captured piece */
	int ccolor;    /* side to which the captured piece belongs */
};

#define MAX_MOVES 256;

/* array size for pieceBB array */

#define SIZE 16

/* pieceBB is an array containing bitboards for all pieces */

u64 pieceBB[SIZE];

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

#define OCCUPIED_SQUARES 14
#define EMPTY_SQUARES 15

#endif /* GLOBALS_H_ */
