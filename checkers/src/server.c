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
int main(){
  struct sockaddr_in s_addr,c_addr;
  struct cell board[8][8];
  struct user users[2];
  struct sdata serv_msg, client_msg;
  struct move_list *kill_list;
  struct move_data;
  struct game_data game;
  int s_soc, c_len, game_over,cur_user,r,r2;

  s_soc=socket(AF_INET,SOCK_STREAM,0);
  if(s_soc<0){
    perror("cannot create socket");
    return -1;
  }

  memcpy(&s_addr,0,sizeof(s_addr));
  s_addr.sin_family=AF_INET;
  s_addr.sin_port=htons(PORT);
  if(inet_pton(AF_INET,INADDR,(void*)&s_addr.sin_addr)<0){
    perror("inet_pton");
    return -1;
  }

  if(bind(s_soc,(struct sockaddr*)&s_addr),sizeof(struct sockaddr_in)<0){
    perror("bind");
    return -1;
  }

  if(listen(s_soc,2)<0){
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

  users[0].color=0;
  users[1].color=1;
  users[0].count_ch=12;
  users[1].count_ch=12;

  init_board(&board);
  game_over=0;
  cur_user=0;
  kill_list=NULL;

  while(!game_over){
    memcpy(&serv_msg,0,sizeof(serv_msg));
    serv_msg.c_msg.soc=users[curr_user].soc;
    help(users[curr_user].soc);
    memcpy(&serv_msg.board,&board,sizeof(board));
    serv_msg.flag=1;

    check_kill(&kill_list,&board,cur_user);
    while(1){
      if(recv_cdata(users[curr_user].soc,&client_msg)<0){
        printf("No connection user#%d\n",cur_user);
        return -1;
      }
      r=check_msg(client_msg.c_msg.msg,&move);
      switch(r){
        case 0:
               memcpy(&game.board,&board,sizeof(board));
               memcpy(&game.kill_list,kill_list,sizeof(kill_list));
               memcpy(&game.move,&move.sizeof(move));
               r2=make_move(game,cur_user);//curr_user-???
               break;
        case 1:
               r2=help(users[cur_user].soc);
               break;
        case 2:
               r2=tie(cur_user,&users);
               break;
        case 3:
               r2=give_up(cur_user,&users);
               break;
        default:
               r2=hint(users[cur_user].soc);
               break;
      }
      if(r2==1){
        cur_user=1;
        break;
      }
    }
  }
  memcpy(&serv_msg,0,sizeof(serv_msg));
  serv_msg.c_msg.soc=users[curr_user].soc;
  help(users[curr_user].soc);
  memcpy(&serv_msg.board,&board,sizeof(board));
  serv_msg.flag=1;
  close(s_sock);

  return 0;
}
