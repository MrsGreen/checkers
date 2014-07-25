#include "check_msg.h"
/*
 * Send help message
 * \return -1 - error
 */
int help(struct sdata *data){
  char text[]="\t\t\tDear user!\nWelcome to 'Russian checkers'\nIf you want to make move type somthing like: A3-B4\nIf you want to ask tie, type: tie\nIf you want to give up, type: giveup\n";
  strcpy(data->c_msg.msg,text);
  if(send_sdata(data)<0){
    return -1;
  }
  return 0;
}