#include "make_move.h"
void set_board(struct move_data move, struct cell*** board){
  int i, j, forward, backward, right, left;

  /* for simple_move */
  board[move.i2][move.j2].empty = 2;
  board[move.i2][move.j2].ch.color = board[move.i1][move.j1].ch.color;
  board[move.i2][move.j2].ch.king = board[move.i1][move.j1].ch.king;

  board[move.i1][move.j1].empty = 1;
  board[move.i1][move.j1].ch.color = 0;
  board[move.i1][move.j1].ch.king = 0;

  /* for kill_move or king_move */
  if (move.i1 > move.i2){
    forward = 1;
    backward = 0;
  }
  else{
    forward = 0;
    backward = 1;
  }
  if (move.j1 > move.j2){
    right = 0;
    left = 1;
  }
  else{
    right = 1;
    left = 0;
  }
  
  /* clear killed checker */
  if (forward && left){
    for (i = move.i1-1; i > move.i2; i--){
      for (j = move.j1-1; j > move.j2; j--){
        board[i][j].empty = 1;
        board[i][j].ch.color = 0;
        board[i][j].ch.king = 0;
      }
    }
  }

  if (forward && right){
    for (i = move.i1-1; i > move.i2; i--){
      for (j = move.j1+1; j < move.j2; j++){
        board[i][j].empty = 1;
        board[i][j].ch.color = 0;
        board[i][j].ch.king = 0;
      }
    }
  }

  if (backward && left){
    for (i = move.i1+1; i < move.i2; i++){
      for (j = move.j1-1; j > move.j2; j--){
        board[i][j].empty = 1;
        board[i][j].ch.color = 0;
        board[i][j].ch.king = 0;
      }
    }
  }

  if (backward && right){
    for (i = move.i1+1; i < move.i2; i++){
      for (j = move.j1+1; j < move.j2; j++){
        board[i][j].empty = 1;
        board[i][j].ch.color = 0;
        board[i][j].ch.king = 0;
      }
    }
  }
  
}