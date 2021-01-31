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
int tally(board_wrap* to_tally);
char highest(int up, int down, int left, int right);
char direction(board_wrap* board, board_wrap* copy);
void move(board_wrap* board, board_wrap* copy);
int end_game(board_wrap* board, board_wrap* copy);
void copy_board(board_wrap* board, board_wrap* copy);
int equals_board(board_wrap* board, board_wrap* copy);
void print_board(board_wrap* board);
