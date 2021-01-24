#include <stdio.h>
#include <stdlib.h>
#include "2048.h"
#include <time.h>

//TODO: set up actual gameplay
//      set up choice-making algorithm

void create_board(board_wrap* board, int size){
    // This function initializes the board to 0 and places the initial two
    // numbers.
    board->size = size;
    int i, j;

    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            board->board[i][j] = 0;
        }
    }
    
    /*int x1 = rand()%8;
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
    board->board[x2][y2] = 1;*/

    add_random(board);
    add_random(board);
}

void add_random(board_wrap* board){
    int x = rand() % board->size;
    int y = rand() % board->size;
    int prob = rand() % 10;
    int add;
    int placed = 0;

    if(prob==0){
        add = 2;
    }
    else{
        add = 1;
    }

    if(board->board[x][y]==0){
        board->board[x][y] = add;
        placed = 1;
    }
    else{
        for(x=x; x<board->size; x++){
            for(y=y; y<board->size; y++){
                if(board->board[x][y]==0){
                    board->board[x][y] = add;
                    placed = 1;
                    break;
                }
            }
            if(placed==1){
                break;
            }
        }
    }
    if(!placed){
        for(x=0; x<board->size; x++){
            for(y=0; y<board->size; y++){
                if(board->board[x][y]==0){
                    board->board[x][y] = add;
                    break;
                }
            }
        }

    }
}

//The next four functions cycle through the board from top to bottom, left to
//right eight times and push all of the numbers in the given direction,
//combining them as necessary.

void push_up(board_wrap* board){
    int i, j, k;
    for(i=0; i<board->size; i++){
        for(j=1; j<board->size; j++){
            for(k=0; k<board->size; k++){
                if(board->board[j][k]!=0){
                    if(board->board[j-1][k] == 0){
                        board->board[j-1][k] = board->board[j][k];
                        board->board[j][k] = 0;
                    }

                    if(board->board[j-1][k] == board->board[j][k]){
                        board->board[j-1][k]++;
                        board->board[j][k] = 0;
                    }
                }
            }
        }
    }
}

void push_down(board_wrap* board){
    int i, j, k;
    for(i=0; i<board->size; i++){
        for(j=board->size-2; j>=0; j--){
            for(k=0; k<board->size; k++){
                if(board->board[j][k]!=0){
                    if(board->board[j+1][k] == 0){
                        board->board[j+1][k] = board->board[j][k];
                        board->board[j][k] = 0;
                    }

                    if(board->board[j+1][k] == board->board[j][k]){
                        board->board[j+1][k]++;
                        board->board[j][k] = 0;
                    }
                }
            }
        }
    }
}

void push_left(board_wrap* board){
    int i, j, k;
    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            for(k=1; k<board->size; k++){
                if(board->board[j][k]!=0){
                    if(board->board[j][k-1] == 0){
                        board->board[j][k-1] = board->board[j][k];
                        board->board[j][k] = 0;
                    }

                    if(board->board[j][k-1] == board->board[j][k]){
                        board->board[j][k-1]++;
                        board->board[j][k] = 0;
                    }
                }
            }
        }
    }
}

void push_right(board_wrap* board){
    int i, j, k;
    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            for(k=board->size-2; k>=0; k--){
                if(board->board[j][k]!=0){
                    if(board->board[j][k+1] == 0){
                        board->board[j][k+1] = board->board[j][k];
                        board->board[j][k] = 0;
                    }

                    if(board->board[j][k+1] == board->board[j][k]){
                        board->board[j][k+1]++;
                        board->board[j][k] = 0;
                    }
                }
            }
        }
    }
}

int tally(board_wrap* to_tally){
    int count = 0;
    int i, j;
    for(i=0; i<to_tally->size; i++){
        for(j=0; j<to_tally->size; j++){
            count += to_tally->board[i][j] * to_tally->board[i][j];
        }
    }
    return count;
}

char highest(int up, int down, int left, int right){
    if(up > down){
        if(left > right){
            if(up > left){
                return 'u';
            }
            else {
                return 'l';
            }
        }
        else{
            if(up > right){
                return 'u';
            }
            else {
                return 'r';
            }
        }
    }
    else {
        if(left > right){
            if(left > down){
                return 'l';
            }
            else {
                return 'd';
            }
        }
        else {
            if(right > down){
                return 'r';
            }
            else {
                return 'd';
            } 
        }
    }
}

char direction(board_wrap* board, board_wrap* copy){
    int up, down, left, right;

    copy_board(board, copy);
    push_up(copy);
    up = tally(copy);

    copy_board(board, copy);
    push_down(copy);
    down = tally(copy);
    
    copy_board(board, copy);
    push_left(copy);
    left = tally(copy);
    
    copy_board(board, copy);
    push_right(copy);
    right = tally(copy);

    return highest(up, down, left, right);
}

void move(board_wrap* board, board_wrap* copy){
    char to_move = direction(board, copy);
    switch(to_move) {
        case 'u':
            push_up(board);
            break;
        case 'd':
            push_down(board);
            break;
        case 'l':
            push_left(board);
            break;
        case 'r':
            push_right(board);
            break;
    }
}

void copy_board(board_wrap* board, board_wrap* copy){
    int i, j;
    copy->size = board->size;
    
    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            copy->board[i][j] = board->board[i][j];
        }
    }
}

void print_board(board_wrap* board){
    //This function prints the board
    int i, j;
    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            printf("%02d ", board->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(char* argv, int argc){
    srand(time(NULL));
    board_wrap board;
    create_board(&board, 8);
    board_wrap copy;
    create_board(&copy, 8);
    copy_board(&board, &copy);
    print_board(&board);
    print_board(&copy);
    /*push_up(&board);
    print_board(&board);
    push_down(&board);
    print_board(&board);
    push_left(&board);
    print_board(&board);
    push_right(&board);
    print_board(&board);*/
    add_random(&board);
    print_board(&board);
    move(&board, &copy);
    print_board(&board);
    return 0;
}
