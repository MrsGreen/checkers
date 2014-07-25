#include "make_move.h"
int check_simple(struct move_data move, struct cell board[8][8], int cur_user){
  int r = 1, forward, backward, right, left, i, j;

  /* check the cur_user */
  if (board[move.i1][move.j1].ch.color != (cur_user + 1)){
    r =0;
  }

  if (board[move.i1][move.j1].ch.king == 0){ //for not king
    if (abs(move.j1 - move.j2) != 1){
      r = 0;
    }
    if (board[move.i1][move.j1].ch.color == 1){ //for white checker
      if ((move.i1 - move.i2) != 1){
        r = 0;
      }
    }
    if (board[move.i1][move.j1].ch.color == 2){ //for black checker
      if ((move.i2 - move.i1) != 1){
        r = 0;
      }
    }
  }

  else{ //for king
    if (((move.i2 + move.j2) % 2) == 0){ //i2 and j2 offside cell
      r = 0;
    }
    if (abs(move.i1 - move.i2) != abs(move.j1 - move.j2)){ //not diagonal move
      r = 0;
    }
    /* determine the direction of move */
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

    /* check the empty of the way */
    if (forward && left){
      for (i = move.i1-1; i >= move.i2; i--){
        for (j = move.j1-1; j >= move.j2; j--){
          if (board[i][j].empty != 1){
            r = 0;
          }
        }
      }
    }

    if (forward && right){
      for (i = move.i1-1; i >= move.i2; i--){
        for (j = move.j1+1; j <= move.j2; j++){
          if (board[i][j].empty != 1){
            r = 0;
          }
        }
      }
    }

    if (backward && left){
      for (i = move.i1+1; i <= move.i2; i++){
        for (j = move.j1-1; j >= move.j2; j--){
          if (board[i][j].empty != 1){
            r = 0;
          }
        }
      }
   }

    if (backward && right){
      for (i = move.i1+1; i <= move.i2; i++){
        for (j = move.j1+1; j <= move.j2; j++){
          if (board[i][j].empty != 1){
            r = 0;
          }
        }
      }
    }

  }
                        
  return r;
}