#include <stdio.h>
#include "defines.h"

int main() {
    // Check
    AllInt();

  

    U64 playBitBoard = 0Ull;
    printf("start:\n");

    PrintBitBoard(playBitBoard);

    playBitBoard |= (1ULL << SQ64(D2));
    printf("D2 add \n");
    PrintBitBoard(playBitBoard);

    playBitBoard |= (1ULL << SQ64(G2));
    printf("G2 add \n");
    PrintBitBoard(playBitBoard);


    // int index = 0;

    // for(index = 0; index < BRD_SQ_NUM; ++index) {
    //     if(index%10 ==0) {
    //         printf("\n");
    //     }
    //     printf("%5d ", Sq120ToSq64[index]);
    // }
    // printf("\n");
    // printf("\n");

    // for(index = 0; index < 64; ++index) {
    //     if ( index % 8 == 0) {
    //         printf("\n");
    //     } 
    //     printf("%5d ", Sq64ToSq120[index]);
    // }
    return 0;
}