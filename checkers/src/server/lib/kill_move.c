int kill_move(struct game_data gdata, int cur_user){
  int check;
  struct sdata dest;
  memset(dest,0,sizeof(dest));

  check_kill2(gdata.move.i1, gdata.move.j1, gdata.kill_list, gdata.&board, cur_user);
  check = list_data(gdata.kill_list, gdata.move);
  if (check == -1){ //if the move does not belong to kill-list
    strcpy(dest.c_msg.msg,"Sorry, you must make a correct kill-move");
    if (send_sdata(dest) < 0){
      return -1; // move has not been made
    }  
    return 0;   
  }

  /* make move */
  set_board(struct gdata.move, gdata.&board);
  check_king(gdata.move.i2, gdata.move.j2, gdata.&board);

  return 1;
}