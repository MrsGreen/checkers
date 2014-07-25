#include <math.h>
#include "../../inc/global.h"

int make_move(struct game_data, int);
void check_king(int, int, struct cell board[8][8]);
void set_board(struct move_data, struct cell board[8][8]);

int simple_move(struct move_data, struct cell board[8][8], int);
int check_simple(struct move_data, struct cell board[8][8], int);

int kill_move(struct game_data, int);
void check_kill2(int, int, struct move_list**, struct cell board[8][8], int);
void check_kill(struct move_list**, struct cell board[8][8], int); 