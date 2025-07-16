// init.c
#include "defines.h"

// random 64 bit number
#define RAND_64 ( (U64)rand() | \
                ((U64)rand() << 15) | \
                ((U64)rand() << 30) | \
                ((U64)rand() << 45) | \
                ((U64)rand() & 0xf) << 60)

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120]; // 13 piece types, 120 squares
U64 SideKey; // key for side to move    
U64 CastleKeys[16]; // 16 castle permissions

void initHashKeys() {
    int index = 0;
    for(index = 0; index < 13; ++index) {
        for(int sq = 0; sq < 120; ++sq) {
            PieceKeys[index][sq] = RAND_64;
        }
    }
    SideKey = RAND_64;
    
    for(index = 0; index < 16; ++index) {
        CastleKeys[index] = RAND_64;
    }
}   

void initBitMasks() {
    int index = 0;
    for (index = 0; index < 64; ++index) {
        SetMask[index] = 0ULL; // initialize to zero
        
        ClearMask[index] = 0ULL; // initialize to zero
    }
    for(index = 0; index < 64; ++index) {
        SetMask[index] = (1ULL << index);
        ClearMask[index] = ~(1ULL << index);
    }
}

void InitSq120ToSq64() {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;

    for(index = 0; index < BRD_SQ_NUM; ++index) {
        Sq120ToSq64[index] = 65; // invalid square
    }
    for(index = 0; index < 64; ++index) {
        Sq64ToSq120[index] = 120; // invalid square
    }
    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            Sq120ToSq64[sq] = sq64;
            Sq64ToSq120[sq64] = sq; 
            sq64++;
        }
    }
}


void AllInt() {

    InitSq120ToSq64();
    initBitMasks();
}