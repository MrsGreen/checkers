int make_move(struct game_data gdata, int cur_user){
  int r;
  if (gdata.kill_list != NULL){
    r = kill_move(gdata, cur_user);
  }
  else{
    r = simple_move(gdata.move, &gdata.board, cur_user);
  }
  return r;
}