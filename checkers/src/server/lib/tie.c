#include "check_msg.h"
/*
 * tie. if success set users->count_ch=0
 * \param current - caller number
 * \param users - users data
 * \return -1 - error, 1 - end input
 */
int tie(int current,struct user **users){
  char text1[]=" gamer wants tie. Yes/No?\n";
  char text2[]=" gamer didn't say Yes. You can continue or giveup\n";
  char color[5];
  struct sdata dest;
  struct cdata answer;

  memset(&dest,0,sizeof(dest));

  if(current==0){
    strcpy(dest.c_msg.msg,"White");
    strcpy(color,"Black");
  }
  else{
    strcpy(dest.c_msg.msg,"Black");
    strcpy(color,"White");
  }
  dest.c_msg.soc=users[!current]->soc;
  strcat(dest.c_msg.msg,text1);
  if(send_sdata(dest)<0){
    return -1;
  }

  if(recv_sdata(dest.c_msg.soc,&answer)<0){
    return -1;
  }
  if(!strcmp(answer.msg,"Yes") || !strcmp(answer.msg,"Y") || 
     !strcmp(answer.msg,"YES") || !strcmp(answer.msg,"yes")){
    return 1;
  }


  memset(&dest,0,sizeof(dest));
  strcat(dest.c_msg.msg,color);
  strcat(dest.c_msg.msg,text2);
  dest.c_msg.soc=users[current]->soc;
  if(send_sdata(dest)<0){
    return -1;
  }
  return 0;
}