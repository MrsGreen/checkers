#include "make_move.h"
int simple_move(struct move_data move, struct cell*** board, int cur_user){
  int check;
  struct sdata dest;
  memset(dest,0,sizeof(dest));


  check = check_simple(move, &board, cur_user);
  if (check == 0){
    strcpy(dest.c_msg.msg,"Incorrect move, use 'help' for more information");
    if (send_sdata(dest) < 0){
      return -1; // move has not been made
    }  
    return 0;   
  }

  /* make move */
  set_board(move, &board);
  check_king(move.i2, move.j2, &board);
  
  return 1;
}