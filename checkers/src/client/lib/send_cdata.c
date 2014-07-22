#include"cdata.h"
/*
 * send message to server
 * \param soc - socket
 * \param data - client's data
 * \return -1 - error
 */
int send_cdata(int soc, struct cdata data){
  if(write(soc,(void *)data,sizeof(data),0)<0){
    return -1;
  }
  return 0;
}