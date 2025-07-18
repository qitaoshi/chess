//data.c
#include "defines.h"


char PceChar[] = ".PNBRQKpnbrqk"; // piece characters, 13 types
char SideChar[] = "wb-"; // white and black
char RankChar[] = "12345678"; // ranks 1 to 8'
char FileChar[] = "abcdefgh"; // files a to hss


int PieceBig[13] = {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE};// big pieces
int PieceMaj[13] = {FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE}; // major pieces
int PieceMin[13] = {FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE}; // minor pieces
int PieceVal[13] = {0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 5000}; // piece values
int PieceCol[13] = {BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}; // piece colors