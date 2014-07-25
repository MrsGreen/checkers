#include "cdata.h"
/*
 * receive message from server
 * \param soc - socket
 * \param data - received data
 * \return -1 - error
 */
int recv_cdata(int soc,struct sdata* data){
  if(read(soc,(void *)data,sizeof(struct sdata))<0){
    return -1;
  }
  
  return 0;
}