#include "inc/global.h"
#include "client/inc/client.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h> 

int main() {
	struct cell board[8][8];
  int domain, type, protocol, sockid;
  struct sockaddr_in addr;
  struct cdata client_msg;
  struct sdata serv_msg;

  domain = AF_INET;
  type=SOCK_STREAM;
  protocol = 0;
  sockid = socket(domain, type, protocol);
  if(sockid < 0){
    perror("can not create socket");
    return -1;
  }
  memcopy(&addr, 0, sizeof(addr));
  addr.sin_family = domain;
  addr.sin_port = htons(PORT);
  
  if(inet_pton(domain, INADDR, (void*)&addr.sin_addr)<0){
    perror("inet_pton");
    return -1;
  }
  if(connect(sockid, (struct sockaddr *)&addr, sizeof(addr)) < 0){
    perror("connect");
    return -1;
  }

  while(!game_over){
    if (recv_sdata(sockid, &serv_msg) < 0){
    	printf("No connection server\n");
    	return -1;
    }

    refresh_screen(board, serv_msg);

    fgets(client_msg, sizeof(client_msg), stdin);
    if(send_cdata(client_msg) < 0){
      printf("No connection server\n");
    }
  }

  close(sockid);
	return 0;
}
