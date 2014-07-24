#include "make_move.h"
void check_kill(struct move_list** kill_list, struct cell*** board, int cur_user){
  int i,j;
  for (i = 0; i < 7; i++){
    for (j = 0; j < 7; j++){
      if (board[i][j].ch.color == (cur_user + 1)){ //if this is your checker
        check_kill2(i, j, kill_list, &board, cur_user);
      }
    }
  }
}