#include "check_msg.h"
/*
 * Send help message
 * \param soc - socket
 * \return -1 - error
 */
int help(int soc){
  struct sdata data;
  char text[]="\t\t\tDear user!\nWelcome to 'Russian checkers'\nIf you want to make move type somthing like: A3-B4\nIf you want to ask tie, type: tie\nIf you want to give up, type: giveup\n";

  memset(data,0,sizeof(data));
  strcpy(data.c_msg.msg,text);
  data.c_msg.soc=soc;

  if(send_sdata(data)<0){
    return -1;
  }
  return 0;
}