#include "init.h"

void init_board(struct cell board[8][8]){
  int i,j;
  
  for (i = 0; i < 8; i++){
    for (j = 0; j < 8; j++){
      board[i][j].ch.king = 0;

      if (((i + j) % 2) == 0){ 
        board[i][j].empty = 0; //offside cells
        board[i][j].ch.color = 0;
      }
      else{
        if (i < 3){
          board[i][j].empty = 2; //game not empty cells
          board[i][j].ch.color = 2; //black checker
        }
        else{
          if ((i > 4)){
            board[i][j].empty = 2; //game not empty cells
            board[i][j].ch.color = 1; //white checker
          }
          else{
            board[i][j].empty = 1; //game empty cells
            board[i][j].ch.color = 0;
          }
        }
      }

    }
  }
}