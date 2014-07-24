#include "kill_list.h"
/*
 * add value val to list head without repeat
 * \param head - head of list
 * \param val - value to add
 */
void list_add(struct move_list **head,struct move_data val){
  struct move_list *p;

  for(p=*head;p!=NULL;p=p->next){
    if((p->move.i1==val.i1) && (p->move.j1==val.j1) 
    && (p->move.i2==val.i2) && (p->move.j2==val.j2)){
      return;
    }
  }
  list_push(head,val);
}
