#include"check_msg.h"
/*
 * Send hint message
 * \param soc - socket
 * \return -1 - error
 */
int hint(int soc){
  struct sdata data;
  char text[]="Wrong message format. Please type help\n"

  memset(data,0,sizeof(data));
  strcpy(data.c_msg.msg,text);
  data.c_msg.msg.soc=soc;

  if(send_sdata(data)<0){
    return -1;
  }
  return 0;
}