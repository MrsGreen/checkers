/* global include */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* global vars */
#define MSG_MAX 1024
#define INADDR "127.0.0.1" //loopback. broadcast?
#define PORT 3425
int game_over;

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
  struct cell board[8][8];
  struct move_data *kill_list;
  struct move_data move;
};

struct user{
  int soc;
  int color;
};

struct cdata{
  char msg[MSG_MAX];
  int soc;
};

struct sdata{
  struct cell board[8][8];
  struct cdata c_msg;
};

/* global fun */
//void glob_fun();