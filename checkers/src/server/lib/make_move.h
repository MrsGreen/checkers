#include <math.h>

int make_move(struct game_data, int);
void check_king(int, int, struct cell***);
void set_board(struct move_data, struct cell***);

int simple_move(struct move_data, struct cell***, int);
int check_simple(struct move_data, struct cell***, int);

int kill_move(struct game_data, int);
void check_kill2(int, int, struct move_list**, struct cell***, int);
void check_kill(struct move_list**, struct cell***, int); 