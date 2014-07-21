//#include <>

int make_move(struct game_data);
int check_king(int, int);
void set_board(struct move_data, struct cell***);

int simple_move(struct move_data, struct cell***);
int check_simple(struct move_data, struct cell***);

int kill_move(struct game_data);
void check_kill2(int, int, struct move_list**);
void check_kill(struct move_list**);