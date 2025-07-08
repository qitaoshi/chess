// hashkey.c
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

U64 GeneratePosKey(const S_Board *pos) {
    
    int sq = 0;
    int piece = EMPTY;
    U64 finalKey = 0;

    // Add piece keys
    for (sq = 0; sq <= BRD_SQ_NUM; ++sq) {
        piece = pos->pieces[sq];
        if(piece != NoSQ && piece != EMPTY) {
            assert(piece >= wP && piece <= bK);

            finalKey ^= PieceKeys[piece][sq];
        }
    
    }
    if(pos->side == WHITE) {
        finalKey ^= SideKey; // Add side key
    }
    if(pos->enPas != NoSQ) {
        assert(pos->enPas >= A1 && pos->enPas <= H8);
        finalKey ^= PieceKeys[EMPTY][pos->enPas];
    }
    
    assert(pos->castlePerm >= 0 && pos->castlePerm < 16);
    
    finalKey ^= CastleKeys[pos->castlePerm]; // Add castle permissions
    return finalKey;
    // Add side key
 
}
