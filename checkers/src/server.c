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
  struct game_data game;
  int sockid, c_len,cur_user,r,r2 = 0, i, j, count_ch, flag;

  sockid = socket(AF_INET, SOCK_STREAM, 0);
  if (sockid < 0){
    perror("cannot create socket");
    return -1;
  }
  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, INADDR, (void*)&s_addr.sin_addr)<0){
    perror("inet_pton");
    return -1;
  }

  if(bind(sockid,(struct sockaddr*)&s_addr,sizeof(s_addr)),sizeof(struct sockaddr_in)<0){
    perror("bind");
    return -1;
  }

  if (listen (sockid, 2) < 0){
    perror("listen");
    return -1;
  }

  users[0].soc=accept(sockid,(struct sockaddr*)&c_addr,&c_len);
  if(users[0].soc<0){
    perror("accept user[0]");
    return -1;
  }

  users[1].soc=accept(sockid,(struct sockaddr*)&c_addr,&c_len);
  if(users[1].soc<0){
    perror("accept user[1]");
    return -1;
  }

  //choose the color?
  users[0].color=0;
  users[1].color=1;

  
  init_board(board);

  game_over=0;
  cur_user=0;
  kill_list=NULL;

  memset(&serv_msg,0,sizeof(serv_msg));
  serv_msg.c_msg.soc=users[cur_user].soc;
  memcpy(serv_msg.board,board,sizeof(board));
  help(&serv_msg);

  memset(&serv_msg,0,sizeof(serv_msg));
  serv_msg.c_msg.soc=users[!cur_user].soc;
  memcpy(serv_msg.board,board,sizeof(board));
  help(&serv_msg);

  while(!game_over){

    memset(&serv_msg,0,sizeof(serv_msg));
    serv_msg.c_msg.soc=users[cur_user].soc;
    memcpy(&serv_msg.board,&board,sizeof(board));
    if (send_sdata(&serv_msg) < 0){
      printf("No connection user#%d\n",cur_user);
      return -1;
    }

    check_kill(&kill_list,board,cur_user);


    /* lose game over */
    /*if (kill_list == NULL){
    	for (i = 0, flag = 0; i < 8, flag == 0; i++){
    		for (j = 0; j < 8; j++){
    			
    		  if (board[i][j].ch.color == (cur_user +1)){ //if meet my checker
    		  game_over = 1; //your checkers can't move
    			printf("after game_over = 1 i=%dj=%d\n",i,j); //отладка
            if ( ((board[i][j].ch.color == 1) && ((i-1) >= 0) && ((j-1) >= 0) && (board[i-1][j-1].empty == 1)) || //for not king
                 ((board[i][j].ch.color == 1) && ((i-1) >= 0) && ((j+1) <= 7) && (board[i-1][j+1].empty == 1)) ||
                 ((board[i][j].ch.color == 2) && ((i+1) <= 7) && ((j+1) <= 7) && (board[i+1][j+1].empty == 1)) || 
                 ((board[i][j].ch.color == 2) && ((i+1) <= 7) && ((j-1) >= 0) && (board[i+1][j-1].empty == 1)) || 
                 ((board[i][j].ch.king == 1) && (board[i][j].ch.color == 2) && ((i-1) >= 0) && ((j-1) >= 0) && (board[i-1][j-1].empty == 1)) || //for king
                 ((board[i][j].ch.king == 1) && (board[i][j].ch.color == 2) && ((i-1) >= 0) && ((j+1) <= 7) && (board[i-1][j+1].empty == 1)) ||
                 ((board[i][j].ch.king == 1) && (board[i][j].ch.color == 1) && ((i+1) <= 7) && ((j+1) <= 7) && (board[i+1][j+1].empty == 1)) || 
                 ((board[i][j].ch.king == 1) && (board[i][j].ch.color == 1) && ((i+1) <= 7) && ((j-1) >= 0) && (board[i+1][j-1].empty == 1)) ){ //if free
            	flag =1; 
            	game_over = 0; 
            	printf("after game_over = 0 i=%dj=%d\n",i,j); //отладка
            	break;
            } 
    		  }
    	  }
    	}

    	
    	memset(&serv_msg,0,sizeof(serv_msg));
      serv_msg.c_msg.soc=users[cur_user].soc;
      memcpy(&serv_msg.board,&board,sizeof(board));
     	strcpy(serv_msg.c_msg.msg,"You can't make move. You lose.\n");
     	if (send_sdata(&serv_msg) < 0){
        printf("No connection user#%d\n",cur_user);
        return -1;
      }

    	memset(serv_msg.c_msg.msg,0,sizeof(serv_msg.c_msg.msg));
    	if(cur_user==0){
    		strcpy(serv_msg.c_msg.msg,"White");
    	}
    	else{
    		strcpy(serv_msg.c_msg.msg,"Black");
    	}
    	strcat(serv_msg.c_msg.msg," player can't make move. You win.\n");
    	serv_msg.c_msg.soc=users[!cur_user].soc;
    	if (send_sdata(&serv_msg) < 0){
        printf("No connection user#%d\n",cur_user);
        return -1;
      }
    	break;
    }*/

    while(r2 == 0){ //repeat enter
      if(recv_cdata(users[cur_user].soc,&client_msg) < 0){
        printf("No connection user#%d\n",cur_user);
        return -1;
      }

      r = check_msg(client_msg.c_msg.msg,&move);
      
      switch(r){
        case 0:
               memcpy(&game.board,&board,sizeof(board));
               memcpy(&game.kill_list,kill_list,sizeof(kill_list));
               memcpy(&game.move,&move,sizeof(move));
               r2=make_move(game,cur_user);
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
    }

    /* win game over */
    count_ch = 0;
    for (i = 0; i < 8; i++){
    	for (j = 0; j < 8; j++){
    	  if (((board[i][j].ch.color == 1) && (cur_user == 1)) || ((board[i][j].ch.color == 2) && (cur_user == 0))){
          count_ch += 1; //if meet opponent checker
    	  }
      }
    }
    if (count_ch == 0){
    	game_over = 1; //win game_over 
    	memcpy(&serv_msg,0,sizeof(serv_msg));
      memcpy(&serv_msg.board,&board,sizeof(board));
      serv_msg.c_msg.soc=users[cur_user].soc;
      strcat(serv_msg.c_msg.msg,"You win. Congratulation!\n");
      if (send_sdata(&serv_msg) < 0){
        printf("No connection user#%d\n",cur_user);
        return -1;
      }

      memcpy(serv_msg.c_msg.msg,0,sizeof(serv_msg.c_msg.msg));
      strcat(serv_msg.c_msg.msg,"You lose.\n");
       serv_msg.c_msg.soc=users[!cur_user].soc;
      if (send_sdata(&serv_msg) < 0){
        printf("No connection user#%d\n",!cur_user);
        return -1;
      }
    }  

    /* change cur_user */
    if (cur_user == 0){
    	cur_user = 1;
    }
    else{
       cur_user = 0;
    }

    list_clear(&kill_list);
  }

  close(sockid);
  return 0;
}
