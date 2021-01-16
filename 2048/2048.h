const int BOARD_SIZE = 8;

typedef struct board_wrap {
    int board[8][8];
    int size;
} board_wrap;

void create_board(board_wrap* board, int size);
void print_board(board_wrap* board);
