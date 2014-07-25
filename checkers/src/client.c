#include "inc/global.h"
#include "client/inc/client.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h> 

int main() {
	struct cell board[8][8];
  int domain, type, protocol, sockid, conid;
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

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = domain;
  addr.sin_port = htons(PORT);

  if(inet_pton(domain, INADDR, (void*)&addr.sin_addr)<0){
    perror("inet_pton");
    return -1;
  }
  conid = connect(sockid, (struct sockaddr *)&addr, sizeof(addr));
  if(conid < 0){
    perror("connect");
    return -1;
  }

  memset(&client_msg, 0, sizeof(client_msg));
  client_msg.soc = sockid;

  while(!game_over){
    if (recv_cdata(sockid, &serv_msg) < 0){
    	printf("recv: no connection server\n");
    	return -1;
    }

    memcpy(board,serv_msg.board,sizeof(board));
    refresh_screen(board, serv_msg.c_msg.msg);

    fgets(client_msg.msg, sizeof(client_msg.msg), stdin);
    if(send_cdata(&client_msg) < 0){
      printf("send: no connection server\n");
    }
  }

  close(sockid);
	return 0;
}
