#include <stdio.h>
#include <stdlib.h>
#include "2048.h"
#include <time.h>

//TODO: fix move algorithm and bug fixes

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
    
    add_random(board);
    add_random(board);
}

void add_random(board_wrap* board){
    //adds a random number in a random unfilled spot on the board

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
    //counts the value of a board (the sum of its numbers squared)
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
    //evaluates which direction has the highest value
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
    //evaluates which direction to push the board in
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
    //pushes the board in the proper direction
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

int end_game(board_wrap* board, board_wrap* copy){
    //determines if the game should be ended (ie there are no more legal moves)
    int difference = 0;
    
    copy_board(board, copy);
    push_up(copy);
    if(!equals_board(board, copy)){
        return 0;
    }

    copy_board(board, copy);
    push_down(copy);
    if(!equals_board(board, copy)){
        return 0;
    }

    copy_board(board, copy);
    push_left(copy);
    if(!equals_board(board, copy)){
        return 0;
    }

    copy_board(board, copy);
    push_right(copy);
    if(!equals_board(board, copy)){
        return 0;
    }

    return 1;
}

void copy_board(board_wrap* board, board_wrap* copy){
    //copies a board into another board_wrap object
    int i, j;
    copy->size = board->size;
    
    for(i=0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            copy->board[i][j] = board->board[i][j];
        }
    }
}

int equals_board(board_wrap* board, board_wrap* copy){
    //determines if two board_wrap objects are equal. Two board_wrap objects
    //are said to be equal if they have the same board size and the same
    //numbers in every cell of the board
    int i, j;
    if(board->size!=copy->size){
        return 0;
    }
    for(i = 0; i<board->size; i++){
        for(j=0; j<board->size; j++){
            if(board->board[i][j] != copy->board[i][j]){
                return 0;
            }
        }
    }
    return 1;
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

    int i;
    while(!end_game(&board, &copy)){
        add_random(&board);
        move(&board, &copy);

        if(i%100000==0){
            print_board(&board);
        }
        i++;
    }
    return 0;
}
