/*
natalia@P500CA:~/eltex/checkers/checkers temp$ aclocal
natalia@P500CA:~/eltex/checkers/checkers temp$ autoheader
natalia@P500CA:~/eltex/checkers/checkers temp$ libtoolize
natalia@P500CA:~/eltex/checkers/checkers temp$ automake -a -c
natalia@P500CA:~/eltex/checkers/checkers temp$ automake --add-missing
natalia@P500CA:~/eltex/checkers/checkers temp$ autoconf
natalia@P500CA:~/eltex/checkers/checkers temp$ autoreconf
natalia@P500CA:~/eltex/checkers/checkers temp$ ./configure
*/

#include "inc/global.h"
#include "server/inc/server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h> 

int main(){
  struct sockaddr_in s_addr,c_addr;
  struct cell board[8][8];
  struct user users[2];
  struct sdata serv_msg, client_msg;
  struct move_list *kill_list;
  struct move_data move;
  struct game_data game; //мы должны занести board в game?
  int sockid, c_len,cur_user,r,r2 = 0, i, j, count_ch;

  sockid = socket(AF_INET, SOCK_STREAM, 0);
  if (sockid < 0){
    perror("cannot create socket");
    return -1;
  }

  memcpy(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, INADDR, (void*)&s_addr.sin_addr)<0){
    perror("inet_pton");
    return -1;
  }

  if(bind(sockid,(struct sockaddr*)&s_addr),sizeof(struct sockaddr_in)<0){
    perror("bind");
    return -1;
  }

  if (listen (sockid, 2) < 0){
    perror("listen");
    return -1;
  }

  if(accept(users[0].soc,(struct sockaddr*)&c_addr,&c_len)<0){
    perror("accept user[0]");
    return -1;
  }
  if(accept(users[1].soc,(struct sockaddr*)&c_addr,&c_len)<0){
    perror("accept user[1]");
    return -1;
  }

  //choose the color?
  users[0].color=0;
  users[1].color=1;

  users[0].count_ch=12; //ненужное поле
  users[1].count_ch=12;

  init_board(&board);
  game_over=0;
  cur_user=0;
  kill_list=NULL;

  while(!game_over){
    memcpy(&serv_msg,0,sizeof(serv_msg));
    serv_msg.c_msg.soc=users[cur_user].soc;
    help(users[curr_user].soc);
    memcpy(&serv_msg.board,&board,sizeof(board));
    serv_msg.flag=1; //нужен ли?
    if (send_sdata(serv_msg) < 0){
      printf("No connection user#%d\n",cur_user);
      return -1;
    }
    
    check_kill(&kill_list,&board,cur_user);

    while(r2 == 0){ //repeat enter
      if(recv_cdata(users[curr_user].soc,&client_msg) < 0){
        printf("No connection user#%d\n",cur_user);
        return -1;
      }

      r = check_msg(client_msg.c_msg.msg,&move);
      
      switch(r){
        case 0:
               memcpy(&game.board,&board,sizeof(board));
               memcpy(&game.kill_list,kill_list,sizeof(kill_list));
               memcpy(&game.move,&move.sizeof(move));
               r2=make_move(game,cur_user);
               break;
        case 1:
               r2=help(users[cur_user].soc);
               break;
        case 2:
               r2=tie(cur_user,&users); //when return 0 ?
               break;
        case 3:
               r2=give_up(cur_user,&users);
               break;
        default:
               r2=hint(users[cur_user].soc);
               break;
      }
    }

    /* game over */
    count_ch = 0;
    for (i = 0; i < 7; i++){
    	for (j = 0; j < 7; j++){
    	  if (((board[i][j].ch.color == 1) && (cur_user == 1)) || ((board[i][j].ch.color == 2) && (cur_user == 0))){
          count_ch += 1; //if meet opponent checker
    	  }
      }
    }
    if (count_ch == 0){
    	game_over = 1; //win game_over 
    }  //под вопросом - запертые шашки

    /* change cur_user */
    if (cur_user == 0){
    	cur_user = 1;
    }
    else{
       cur_user = 0;
    }
  }

  /*  send msg about result of game */
  //memcpy(&serv_msg,0,sizeof(serv_msg));
  //serv_msg.c_msg.soc=users[cur_user].soc;
  //send_sdata - cur юзеру. а другому - что? где рез-т исхода партии?
  //memcpy(&serv_msg.board,&board,sizeof(board));

  close(sockid);
  return 0;
}
