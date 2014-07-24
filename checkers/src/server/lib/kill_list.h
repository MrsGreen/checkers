#include "../../inc/global.h"
#include <malloc.h>

void list_push(struct move_list **,struct move_data);
void list_pop(struct move_list **,struct move_data);
void list_add(struct move_list **,struct move_data);
void list_clear(struct move_list **);
int list_data(struct move_list **,struct move_data);