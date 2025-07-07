// hashkey.c
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    AllInt();
    int PieceOne = rand();
    int PieceTwo = rand();
    int PieceThree = rand();
    int PieceFour = rand();

    int key = PieceOne ^ PieceTwo ^ PieceThree ^ PieceFour;
    int tempkey =  PieceOne;
    tempkey ^= PieceTwo;
    tempkey ^= PieceThree;
    tempkey ^= PieceFour;
}
