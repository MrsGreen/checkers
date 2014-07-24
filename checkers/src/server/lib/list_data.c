#include"kill_list.h"
/*
 * check val in list
 * \param head - head of list
 * \param val - value to check
 * \return 1 - true -1 - false
 */
int list_data(struct move_list **head,struct move_data val){
  struct list *move_list p;

  for(p=*head;p!=NULL;p=p->next){
    if((p->move.i1==val.i1) && (p->move.j1==val.j1)
       && (p->move.i2==val.i2) && (p->move.j2==val.j2)
    ){
      return 1;
    }
  }
  return -1;
}
