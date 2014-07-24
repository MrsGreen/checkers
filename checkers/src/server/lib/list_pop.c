#include "kill_list.h"
/*
 * pop value val from list head
 * \param head - head of list
 * \param val - value to pop
 */
void list_pop(struct move_list **head,struct move_data val){
  struct move_list * p, *q;

  p=*head;
  if(((*head)->move.i1==val.i1) && ((*head)->move.j1==val.j1)
  && ((*head)->move.i2==val.i2) && ((*head)->move.j2==val.j2)){
    *head=(*head)->next;
    free(p);
    return;
  }

  q=p;
  p=p->next;
  while(p!=NULL){
    if((p->move.i1==val.i1) && (p->move.j1==val.j1)
    && (p->move.i2==val.i2) && (p->move.j2==val.j2)){
      q->next=p->next;
      free(p);
      return;
    }
    p=p->next;
  }
}