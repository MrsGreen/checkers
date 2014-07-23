void check_kill2(int i1, int j1, struct move_list** kill_list, struct cell*** board, int cur_user){
  int count_kill, i, j, max_i, max_j;
  struct move_data move;
  move.i1 = i1;
  move.j1 = j1;

  /* forward left move */
  count_kill = 0;
  max_i = i1 - j1;
  if (max_i < 0){
    max_i = 0;
  }
  max_j = j1 - i1;
  if (max_j < 0){
    max_j = 0;
  }

  for (i = i1-1, j = j1-1; i >= max_i, j >= max_j; i--, j--){
    if (board[i][j].ch.color == (cur_user + 1)){ 
      break; //meet my checker
    }
    if (((board[i][j].ch.color == 1) && (cur_user == 1)) || ((board[i][j].ch.color == 2) && (cur_user == 0))){
      count_kill += 1; //meet opponent checker
    }
    if ((board[i][j].empty == 1) && (count_kill == 1)){
      move.i2 = i;
      move.j2 = j;
      list_add(kill_list, move); //add to kill-list
    }
  }

  /* forward right move */
  count_kill = 0;
  max_i = j1 + i1 - 7;
  if (max_i < 0){
    max_i = 0;
  }
  max_j = j1 + i1;
  if (max_j > 7){
    max_j = 7;
  }
  for (i = i1-1, j = j1+1; i >= max_i, j <= max_j; i--, j++){
    if (board[i][j].ch.color == (cur_user + 1)){ 
      break; //meet my checker
    }
    if (((board[i][j].ch.color == 1) && (cur_user == 1)) || ((board[i][j].ch.color == 2) && (cur_user == 0))){
      count_kill += 1; //meet opponent checker
    }
    if ((board[i][j].empty == 1) && (count_kill == 1)){
      move.i2 = i;
      move.j2 = j;
      list_add(kill_list, move); //add to kill-list
    }
  }

  /* backward right move */
  count_kill = 0;
  max_i = 7 + i1 - j1;
  if (max_i > 7){
    max_i = 7;
  }
  max_j = 7 - i1 + j1;
  if (max_j > 7){
    max_j = 7;
  }
  for (i = i1+1, j = j1+1; i <= max_i, j <= max_j; i++, j++){
    if (board[i][j].ch.color == (cur_user + 1)){ 
      break; //meet my checker
    }
    if (((board[i][j].ch.color == 1) && (cur_user == 1)) || ((board[i][j].ch.color == 2) && (cur_user == 0))){
      count_kill += 1; //meet opponent checker
    }
    if ((board[i][j].empty == 1) && (count_kill == 1)){
      move.i2 = i;
      move.j2 = j;
      list_add(kill_list, move); //add to kill-list
    }
  }

  /* backward left move */
  count_kill = 0;
  max_i = i1 + j1;
  if (max_i > 7){
    max_i = 7;
  }
  max_j = i1 + j1 - 7;
  if (max_j < 0){
    max_j = 0;
  }
  for (i = i1+1, j = j1-1; i <= max_i, j >= max_j; i++, j--){
    if (board[i][j].ch.color == (cur_user + 1)){ 
      break; //meet my checker
    }
    if (((board[i][j].ch.color == 1) && (cur_user == 1)) || ((board[i][j].ch.color == 2) && (cur_user == 0))){
      count_kill += 1; //meet opponent checker
    }
    if ((board[i][j].empty == 1) && (count_kill == 1)){
      move.i2 = i;
      move.j2 = j;
      list_add(kill_list, move); //add to kill-list
    }
  }

}