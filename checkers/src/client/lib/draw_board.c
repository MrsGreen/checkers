/*
*function for drawing game board and checkers
*/
void draw_board(struct cell** board){
  int i, j;

  printf("\n ");
  for (i = 0; i < 8; i++){
    printf(" %c", 'A' + i);
  }
  
  printf("\n  ");
  for (i = 0; i < 8; i++){
    printf("--"); //border
  }
  
  for (i = 0; i < 8; i++){
    printf("\n%d|", 8-i);
    for (j = 0; j < 8; j++){
      if(board.empty == 0){ //offside cells
        printf("  ");
      }
      if(board.empty == 1) //game empty cells
        printf("##");
      if(board.empty == 2){ //game not empty cells
        if(board.ch.color == 1){ //white
          if (board.ch.king == 0){ //not king
            printf("w ");
          }
          else{
            printf("W "); //king
          }
        }
        else {
          if (board.ch.color == 2){ //black
            if (board.ch.king == 0){ //not king
              printf("b ");
            }
            else{
              printf("B "); //king
            }
          }
        }
      }
    }
    printf("|%d", 8-i);
  }
    printf("\n");

  for (i = 0; i < 8; i++){
    printf("--");
  }
  
  printf("\n "); 
  for (i = 0; i < 8; i++){
    printf(" %c", 'A' + i);
  }
    printf("\n");
}