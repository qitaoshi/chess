//board.c
#include "defines.h"
#include <stdio.h>

int ParseFen(char *fen, S_Board *pos){
    assert(fen != NULL);
    assert(pos != NULL);

    int rank = RANK_8;
    int file = FILE_A;

    int piece  = 0;
    int count = 0;
    int i = 0;
    int sq64 = 0;
    int sq120 = 0;
    

    ResetBoard(pos);

    while((rank >= RANK_1) && *fen){
        count = 1;
        switch (*fen)
        {
            case 'p' : piece = bP; break;
            case 'r' : piece = bR; break;
            case 'n' : piece = bN; break;
            case 'k' : piece = bK; break;
            case 'q' : piece = bQ; break;
            case 'P' : piece = wP; break;
            case 'R' : piece = wR; break;
            case 'N' : piece = wN; break;
            case 'K' : piece = wK; break;
            case 'Q' : piece = wQ; break;

            case '1': 
            case '2': 
            case '3': 
            case '4': 
            case '5': 
            case '6': 
            case '7': 
            case '8': 
                piece = EMPTY;
                count = *fen - '0'; // convert char to int
                break;
            case '/' : 
            case ' ' : 
                rank--;
                file = FILE_A;
                fen++;
                continue;
            default:
                printf("Unknown FEN character %c\n", *fen);
                return -1;
        }
        // file A B C D E Rank 4
        // 4RKQP

        for (i = 0; i < count; ++i) {
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece; // place the piece on the board
            }
            file++;
        }
        fen++; // move past the space after the rank 
    }
    assert(*fen == ' ' || *fen == '\0'); // ensure we reached the end of the rank

    pos->side = (*fen == 'w') ? WHITE : BLACK; // set the side to move
    fen += 2; // move past the side character and space


    for (i = 0; i < 4; i++) {
        if (*fen == ' ') break; // stop if we reach a space
        switch (*fen) {
            case 'K': pos->castlePerm |= WRCA; break;
            case 'Q': pos->castlePerm |= WQCA; break;
            case 'k': pos->castlePerm |= BRCA; break;
            case 'q': pos->castlePerm |= BQCA; break;
            default:  break;
        }
        fen++;
    }
    fen++; // move past the castle permissions
    assert(pos->castlePerm >= 0 && pos->castlePerm <= 15); // ensure valid castle permissions

    if(*fen != '-') {
        file = fen[0] - 'a'; // convert file character to file index
        rank = fen[1] - '1'; // convert rank character to rank index
        
        assert(file>=FILE_A && file<=FILE_H); // ensure valid file
        assert(rank>=RANK_1 && rank<=RANK_8); // ensure valid rank

        pos->enPas = FR2SQ(file, rank); // set en passant square
    } else {
        pos->enPas = NoSQ; // no en passant square
    }
    pos->posKey = GeneratePosKey(pos); // generate position key
        return 0; // success
}

void ResetBoard(S_Board * pos){

    int index = 0;
    for(index = 0; index < BRD_SQ_NUM; ++index) {
        pos->pieces[index] = OFFBOARD; // initialize all squares to offboard
    }
    for(index = 0; index < 64; ++index) {
        pos->pieces[SQ120(index)] = EMPTY; // initialize valid squares to empty
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

void PrintBoard(const S_Board *pos) {
    int sq,file,rank,piece;

    printf("\nGame Board:\n");
    
    for(rank = RANK_8; rank >= RANK_1; rank--){
        printf("%d ", rank + 1); // print rank number
        for(file = FILE_A; file <= FILE_H; file++) {
            sq = FR2SQ(file, rank);
            piece = pos->pieces[sq];
            printf("%3c ", PceChar[piece]); // print piece character
        }
        printf("\n");
    }
    printf("\n   ");
    for(file = FILE_A; file <= FILE_H; file++) {
        printf("%3c ", 'a' + file); // print file character
    }
    printf("\n");
    printf("Side: %c\n", SideChar[pos->side]); // print side to move
    printf("En Passant: %d\n", pos->enPas); // print en passant square

    printf("castle: %c%c%c%c\n", 
           (pos->castlePerm & WRCA) ? 'K' : '-',
           (pos->castlePerm & WQCA) ? 'Q' : '-',
           (pos->castlePerm & BRCA) ? 'k' : '-',
           (pos->castlePerm & BQCA) ? 'q' : '-');
    printf("PosKey: %llu\n", pos->posKey); // print position key

}
