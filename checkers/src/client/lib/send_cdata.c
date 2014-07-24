#include "cdata.h"
/*
 * send message to server
 * \param data - client's data
 * \return -1 - error
 */
int send_cdata(struct cdata data){
  if(write(data.c_msg.soc,(void)data,sizeof(data),0)<0){
    return -1;
  }
  return 0;
}