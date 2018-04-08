/*
 * Main.c
 *
 *  Created on: May 2, 2017
 *      Author: Amar Thapa
 */

#include <sys\timeb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "globals.h"
#include "utility.h"
#include "magicmoves.h"
#include "nonslidingmoves.h"
#include "init.h"
#include "perft.h"
#include "dynarray.h"

typedef void(*split_fn)(const char *, size_t, void *);
 
void split(const char *str, char sep, split_fn fun, void *data)
{
    unsigned int start = 0, stop;
    for (stop = 0; str[stop]; stop++) {
        if (str[stop] == sep) {
            fun(str + start, stop - start, data);
            start = stop + 1;
        }
    }
    fun(str + start, stop - start, data);
}

void initFEN(const char *str, size_t len, void *data) {
  	dynarray *array = data;
    char *token = calloc(len + 1, 1);
    memcpy(token, str, len);
    dynarray_add_tail(array, token);
}


void print(const char *str, size_t len, void *data)
{
    printf("%.*s\n", (int)len, str);
}
 
 void readFEN(char* FEN, int len) {
	FILE *fptr;
    char ch;

   	fptr = fopen("fen.txt", "r");
  
    if (fptr == NULL)
    {
        printf("Cannot open file for FEN strings \n");
    }
  
    ch = fgetc(fptr);
  
    while (ch != EOF)
    {
        ch = fgetc(fptr);
        FEN[len] = ch;
        len++;
    }
  	
  	FEN[len] = '\0';

  	printf("%s\n", FEN);
    fclose(fptr);
 }


void splitTheFENPlease() {

	int len = 0;
	char str[100];

	readFEN(str, len);

    dynarray *d_array = dynarray_create(0);
    dynarray *mainFEN = dynarray_create(0);

    split(str, ' ', initFEN, d_array);

    switch(((char*)(d_array->buffer[1]))[0]) {
    	case 'w' : color = WHITE; 
    		break;
    	case 'b' : color = BLACK;
    		break;
    	default : color = WHITE;
   			break;
    }

    printf("Side to move : %s\n", color==0?"WHITE":"BLACK");

    for(int i = 0; i < d_array->count; i++) {
    	split(d_array->buffer[i], '/', initFEN, mainFEN);
    }

    for (int i = 0; i < mainFEN->count; i++) {
   		int pos = 0;
    
    	while(((char*)(mainFEN->buffer[i]))[pos] != NULL) {
    		printf("%c ", ((char*)(mainFEN->buffer[i]))[pos]);

    		switch(((char*)(mainFEN->buffer[i]))[pos]) {
    			case 'k':
    		//		printf("%s\n", "White King");
    				break;
				case 'q':
    		//		printf("%s\n", "White Queen");
    				break;
    			case 'b':
    		//		printf("%s\n", "White Bishop");
    				break;
    			case 'n':
    		//		printf("%s\n", "White Knight");
    				break;
    			case 'r':
    		//		printf("%s\n", "White Rook");
    				break;
    			case 'p':
    		//		printf("%s\n", "White Pawns");
    				break;
    		
    			case 'K':
    		//		printf("%s\n", "Black King");
    				break;
				case 'Q':
    		//		printf("%s\n", "Black Queen");
    				break;
    			case 'B':
    		//		printf("%s\n", "Black Bishop");
    				break;
    			case 'N':
    		//		printf("%s\n", "Black Knight");
    				break;
    			case 'R':
    		//		printf("%s\n", "Black Rook");
    				break;
    			case 'P':
    		//		printf("%s\n", "Black Pawns");
    				break;

    			default: //printf("%s\n", "Blank Space");
    				break;
    		}

    		pos += 1;
    	}

    	printf("\n");
    }

	dynarray_for_each(d_array, free);
    dynarray_delete(d_array);
	dynarray_for_each(mainFEN, free);
    dynarray_delete(mainFEN);
    

}

int main(int argc, char **argv) {
	splitTheFENPlease();

	int depth = 0;

	depth = atoi(argv[1]);

	printf("Depth = %d\n", depth);

	struct timeb start, end;
	double diff;

	init_piece_bb(); 
	init_index_bb();
	init_king_attacks();
	init_knight_attacks();
	init_magic_moves(); 

	ply = 0;

	hist_add.move = 0;
	hist_add.ep_flag = 0;
	hist_add.castle_flags = (u8)0x1111;  

	hist[ply] = hist_add;
	
	u8 i;
	u64 nodes;

	printf("\n");

//	divide(depth, WHITE);
	for (int i = 1; i <= depth; i++) {

		ftime(&start);

		nodes = 0;
		quiet = 0;
		cap = 0;
		en = 0;
		cas = 0;
		check = 0;

		color = WHITE;

		nodes = perft(i, color);

		ftime(&end);

		diff = ((1000.0 * (end.time - start.time) 
			+ (end.millitm - start.millitm)) / 1000);
		
		printf("\nDepth(%d)=   ", i);

		printf("%8llu (%.3f sec), color - %s, quiet - %8llu, captures - %8llu, en - %6llu, cas - %6llu, checks - %8llu", nodes, diff, ((color==0) ? "WHITE" : "BLACK"), quiet, cap, en, cas, check);
	}

	return 0;
}


