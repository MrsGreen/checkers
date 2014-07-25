#include "make_move.h"
void check_kill(struct move_list** kill_list, struct cell board[8][8], int cur_user){
  int i,j;
  for (i = 0; i < 8; i++){
    for (j = 0; j < 8; j++){
      if (board[i][j].ch.color == (cur_user + 1)){ //if this is your checker
        check_kill2(i, j, kill_list, board, cur_user);
      }
    }
  }
}