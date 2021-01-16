#include <stdio.h>
#include <stdlib.h>
#include "2048.h"

void create_board(board_wrap* board, int size){
    board->size = size;
    int i, j;

    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            board->board[i][j] = 0;
        }
    }
    
    int x1 = rand()%8;
    int y1 = rand()%8;
    int x2 = rand()%8;
    int y2 = rand()%8;

    if (x1==x2 && y1==y2){
        if(x2<size-1){
            x2 = x2 + 1;
        }
        else{
            x2 = 0;
        }
    }

    board->board[x1][y1] = 1;
    board->board[x2][y2] = 1;
}

void print_board(board_wrap* board){
    int i, j;
    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            printf("%02d ", board->board[i][j]);
        }
        printf("\n");
    }
}

int main(char* argv, int argc){
    board_wrap board;
    create_board(&board, 8);
    print_board(&board);
    return 0;
}
