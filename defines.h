#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <assert.h>


typedef unsigned long long U64;

#define NAME "Quokachi 1.0"
#define BRD_SQ_NUM 120

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define MAXGAMEMOVES 2048
#define MAXPOSITIONMOVES 256
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

typedef struct{
    int move;
    int score;
} S_Move;
typedef struct 
{
    S_Move moves[MAXPOSITIONMOVES];
    int count;
}S_MOVELIST;



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
    int bigPce[2];
    int majPce[2]; // rooks and queens
    int minPce[2]; // bishops and knights
    int material[2]; // material for each side

    S_Undo history[MAXGAMEMOVES];


    // piece lists
    int pList[13][10]; // 13 piece types, max 10 of each type


}S_Board;





/* Game Moves*/
/*


0000 0000 0000 0000 0000 0111 1111 -> FROM SQUARE 0x7f
0000 0000 0000 0011 1111 1000 0000 -> TO SQUARE >> 7, 0x7F
0000 0000 0011 1100 0000 0000 0000 -> capture >> 14 0xF
0000 0000 0100 0000 0000 0000 0000 -> EP 0x40000
0000 0000 1000 0000 0000 0000 0000 -> Pawnstart 0x80000
0000 1111 0000 0000 0000 0000 0000 -> Promotion > 20 0xF
0001 0000 0000 0000 0000 0000 0000 -> castle 0x100000

*/
#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)

#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7C000
#define MFLAGFROM 0xF00000




/* MACROS   */
#define FR2SQ(f,r) ((21 + (f)) + ((r) * 10)) // file rank to square
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLEARBIT(bb,sq) ((bb) &= ClearMask[sq])
#define SETBIT(bb,sq) ((bb) |= SetMask[sq]) 

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])

/*  GLOBALS */
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];

extern U64 PieceKeys[13][120]; // 13 piece types, 120 squares
extern U64 SideKey; // key for side to move    
extern U64 CastleKeys[16]; // 16 castle permissions

extern char PceChar[]; // piece characters
extern char SideChar[]; // side characters
extern char RankChar[]; // rank characters

extern int PieceBig[13]; // big pieces
extern int PieceMaj[13] ;// major pieces
extern int PieceMin[13] ;// minor pieces
extern int PieceVal[13] ;// piece values
extern int PieceCol[13] ;// piece colors

extern int FileBrd[BRD_SQ_NUM];
extern int RankBrd[BRD_SQ_NUM];

extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceRookQueen[13];
extern int PieceBishopQueen[13]; 


/* FUNCTIONS */
// init.c
extern void AllInt();
extern void InitFileRankBrd();


// bitboards.c
extern void PrintBitBoard(U64 bb);
extern int CountBits(U64 b);
extern int PopBit(U64 *bb);

//haskkeys.c
extern U64 GeneratePosKey(const S_Board *pos); 

//board.c
extern void ResetBoard(S_Board *pos);
extern int ParseFen( char *fen, S_Board *pos);
extern void PrintBoard(const S_Board *pos);
extern void UpdateListsMaterials(S_Board *pos);
//attack.c
extern int SqAttack(const int sq, const int side, const S_Board *pos);

//io.c 
extern char *PrMove(const int  move);
extern char *PrSq(const int move);
#endif
