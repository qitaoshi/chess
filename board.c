//board.c
#include "defines.h"
#include <stdio.h>

void Parse_Fen(char *fen, S_Board *pos){
    assert(fen != NULL);
    assert(pos != NULL);

    int rank = RANK_8;
    int file = FILE_A;

    int pieces = 0;
    int count = 0;
    int i = 0;
    int sq64 = 0;
    int sq120 = 0;

    ResetBoard(pos);

    while((rank >= RANK_1) && *fen){
        count = 1;
        switch (*fen)
        {
        case constant expression:
            /* code */
            break;
        
        default:
            break;
        }
    }
}

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