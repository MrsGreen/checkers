#include "make_move.h"
void check_king(int i, int j, struct cell*** board){
  if (((board[i][j].ch.color == 1) && (i == 0)) || ((board[i][j].ch.color == 2) && (i == 7))){
    board[i][j].ch.king = 1;
  }
}