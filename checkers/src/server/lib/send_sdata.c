#include"sdata.h"
/*
 * send data to client
 * \param data - data to send
 * \return -1 - error
 */
int send_sdata(struct sdata data){
  if(write(data.c_msg.soc,(void)data,sizeof(data),0)<0){
  return -1;
  }
  return 0;
}