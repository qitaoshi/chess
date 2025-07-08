#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <assert.h>


typedef unsigned long long U64;

#define NAME "Quokachi 1.0"
#define BRD_SQ_NUM 120
#define sq120 120

#define MAXGAMEMOVES 2048
enum {EMPTY, wP, wN, wB, wR, wQ, wK,
       bP, bN, bB, bR, bQ, bK}; // piece types


enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

enum { WHITE, BLACK, BOTH };

enum{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NoSQ, OFFBOARD
}; // squares on the board
enum {FALSE, TRUE};

enum {WRCA =1, WQCA = 2, BRCA = 4, BQCA = 8}; // castle format  = (colour, side) 0 0 0 0


typedef struct defines
{
    int move;
    int castlePerm;
    int enPas;
    int FiftyMove;
    U64 poskey;
} S_Undo;

typedef struct {
    int pieces[BRD_SQ_NUM];
    U64 pawns[3]; // 0: white, 1: black, 2: both

    int KingSq[2];

    int side; 
    int enPas; // enpassent rule
    int fiftyMove; // 

    int ply;    // seacrch depth
    int hisPly;
    
    int castlePerm;

    U64 posKey;

    int pceNum[13];
    int bigPce[3];
    int majPce[3]; // rooks and queens
    int minPce[3]; // bishops and knights

    S_Undo history[MAXGAMEMOVES];


    // piece lists
    int pList[13][10]; // 13 piece types, max 10 of each type


}S_Board;

/* MACROS   */
#define FR2SQ(f,r) ((21 + (f)) + ((r) * 10)) // file rank to square
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLEARBIT(bb,sq) ((bb) &= ClearMask[sq])
#define SETBIT(bb,sq) ((bb) |= SetMask[sq]) 

/*  GLOBALS */
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];

extern U64 PieceKeys[13][120]; // 13 piece types, 120 squares
extern U64 SideKey; // key for side to move    
extern U64 CastleKeys[16]; // 16 castle permissions


/* FUNCTIONS */
// init.c
extern void AllInt();


// bitboards.c
extern void PrintBitBoard(U64 bb);
extern int CountBits(U64 b);
extern int PopBit(U64 *bb);

//haskkeys.c
extern U64 GeneratePosKey(const S_Board *pos); 

//board.c
extern void ResetBoard(S_Board *pos);


#endif
