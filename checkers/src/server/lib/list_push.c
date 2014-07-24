#include "kill_list.h"
/*
 * push value val into list head
 * \param head - head of list
 * \param val - value
 */
void list_push(struct move_list ** head,struct move_data val){
  struct move_list * p;
  p=( struct move_list *)malloc(sizeof(struct move_list));
  if(p==NULL){
    printf("Push: malloc error\n");
    return;
  }

  p->move.i1=val.i1;
  p->move.j1=val.j1;
  p->move.i2=val.i2;
  p->move.j2=val.j2;

  if(head==NULL){
    p->next=NULL;
  } else {
    p->next=*head;
  }
  *head=p;
}