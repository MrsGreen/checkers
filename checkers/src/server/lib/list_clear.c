#include "kill_list.h"
/*
 * clear list
 * \param head - head of list
 */
void list_clear(struct move_list **head){
  struct move_list * p;

  while((*head)!=NULL){
    p=*head;
    *head=(*head)->next;
    free(p);
  }
}

