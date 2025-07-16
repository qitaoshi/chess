#include <stdio.h>
#include "defines.h"

#define FEN1 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 2"

int main() {
    // Check
    AllInt();

    S_Board board[1];

    ParseFen(START_FEN, board); 
    PrintBoard(board);
    
    ParseFen(FEN1, board);
    PrintBoard(board);

    ParseFen(FEN2, board);
    PrintBoard(board);

    ParseFen(FEN3, board);
    PrintBoard(board);




    return 0;
}