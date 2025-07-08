//board.c
#include "defines.h"
#include <stdio.h>

void ResetBoard(S_Board * pos){

    int index = 0;
    for(index = 0; index < BRD_SQ_NUM; ++index) {
        pos->pieces[index] = OFFBOARD; // initialize all squares to empty
    }
    for(index = 0; index < 13; ++index) {
        pos->pieces[SQ120(index)] = EMPTY; // initialize all pawns to zero
    }
    for (index = 0; index < 3; ++index) {
        pos->bigPce[index] = 0; // initialize big pieces to zero
        pos->majPce[index] = 0; // initialize major pieces to zero
        pos->minPce[index] = 0; // initialize minor pieces to zero
        pos->pawns[index] = 0ULL; // initialize all pawns to zero
    }
    for(index = 0; index < 13; ++index) {
        pos->pceNum[index] = 0; // initialize all piece counts to zero
    }

    pos->KingSq[WHITE] = pos->KingSq[BLACK] = NoSQ; // initialize king squares to invalid
    pos->side = BOTH; // set side to Both
    pos->enPas = NoSQ; // set en passant square to invalid
    pos->fiftyMove = 0; // set fifty move rule to zero

    pos->ply = 0; // set ply to zero
    pos->hisPly = 0; // set history ply to zero

    pos->castlePerm = 0; // set castle permissions to zero
    
    pos->posKey = 0ULL; // set position key to zero
}