#include"sdata.h"
/*
 * receive data from client
 * \param soc - socket
 * \param data - received data
 * \return -1 - error
 */
int recv_sdata(int soc, struct cdata* data){
  if(read(soc,(void*)data,sizeof(struct cdata),0)<0){
    return -1;
  }
  return 0;
}