#include "check_msg.h"
/*
 * set users[current]->count_ch=0
 * \param current - caller number
 * \param users - users data
 * \return -1 - error, 1 - end input
 */
int give_up(int current,struct user **users){
  char text[]=" gamer give up\n";
  struct sdata dest;

  memset(dest,0,sizeof(dest));
  if(current==0){
    strcpy(dest.c_msg.msg,"White");
  }
  else{
    strcpy(dest.c_msg.msg,"Black");
  }
  dest.c_msg.soc=users[!current]->soc;
  strcat(dest.c_msg.msg,text);

  if(send_sdata(dest)<0){
    return -1;
  }
  users[current]->count_ch=0;
  return 1;
}