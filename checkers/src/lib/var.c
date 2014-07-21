#include "var.h"
/*global vars*/

#define MSG_MAX 1024

struct checker{
  int color;
  int king;
};

struct cell{
  struct checker ch;
  int empty;
};

struct move_data{
  int i1;
  int j1;
  int i2;
  int j2;
};

struct move_list{
  struct move_data move;
  struct move_list *next;
};

struct game_data{
  struct cell ***board;
  struct move_data *kill_list;
  struct move_data move;
};

struct user{
  int soc;
  int color;
  int count_ch;
};

struct cdata{
  char msg[MSG_MAX];
  int soc;
};

struct sdata{
  struct cell board[8][8];
  struct cdata c_msg;
  int flag;
};
/*global fun*/
//void glob_fun(){}