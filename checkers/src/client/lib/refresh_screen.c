#include "screen.h"

void refresh_screen(struct cell board[8][8], char* msg){
  system("clear");
  draw_board(board);
  draw_msg(msg);
}
