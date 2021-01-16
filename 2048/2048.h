const int BOARD_SIZE = 8;

typedef struct board_wrap {
    int board[8][8];
    int size;
} board_wrap;

void create_board(board_wrap* board, int size);
void add_random(board_wrap* board);
void push_up(board_wrap* board);
void push_down(board_wrap* board);
void push_left(board_wrap* board);
void push_right(board_wrap* board);
void print_board(board_wrap* board);
