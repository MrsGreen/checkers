void refresh_screen(struct cell** board, char* msg){
  system("clear");
  draw_board(&board);
  draw_msg(msg);
}
