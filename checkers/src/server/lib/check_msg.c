#include"check_msg.h"
/*
 * Parse user's message. Copy user's move from msg to move
 * \param msg - user's message
 * \param move - move coordinates
 * \return message code
 * 0 - move
 * 1 - help
 * 2 - tie
 * 3 - giveup
 * -1 - incorrect message
 */
int check_msg(char* msg, struct move_data* move){
  char tmp[2];
  int num;

  if(!strncmp(msg,"help",4)){
    return 1;
  }
  if(!strncmp(msg,"tie",3)){
    return 2;
  }
  if(!strncmp(msg,"giveup",6)){
    return 3;
  }

  if(strlen(msg)!=5){
    return -1;
  }

  memset(move,0,sizeof(move));
  if((msg[2]=='-')){
    num=(int)msg[0]-(int)'A';
    if((num<0) || (num>7)){
      num=(int)msg[0]-(int)'a';
      if((num<0) || (num>7)){
        return -1;
      }
    }
    move->j1=num;

    memset(tmp,0,sizeof(tmp));
    if((msg[1]>='1') && (msg[1]<='8')){
      strncpy(tmp,&msg[1],1);
      move->i1=8-atoi(tmp);
    }
    else {
      return -1;
    }

    num=(int)msg[3]-(int)'A';
    if((num<0) || (num>7)){
      num=(int)msg[3]-(int)'a';
      if((num<0) || (num>7)){
        return -1;
      }
    }
    move->j2=num;

    memset(tmp,0,sizeof(tmp));
    if((msg[4]>='1') && (msg[4]<='8')){
      strncpy(tmp,&msg[4],1);
      move->i2=8-atoi(tmp);
    }
    else {
      return -1;
    }
    return 0;
  }

  return -1;
}