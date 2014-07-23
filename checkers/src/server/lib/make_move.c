int make_move(struct game_data gdata){
  int r;
  if (gdata.kill_list != 0){
    r = kill_move(gdata);
  }
  else{
    r = simple_move(gdata.move, &gdata.board);
  }
  return r;
}