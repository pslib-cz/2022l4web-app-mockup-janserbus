/**
 * DEFINITIONS OF LIST DATA TYPE (GENARAL PURPOSE DYNAMIC ARRAY)
 * ==========================================================================
 */

#pragma once

#include <stdbool.h>

typedef struct list{
    void **element;
    int size;
    int rear;
}list;

//creates new list of size elements big
list List_create(int size);

//appends new list element, returns true on success else false
bool List_append(list *List, void *listElement);

//removes and frees place element of the list and sorts it afterwards
void List_pop(list *List, const unsigned int place);

//removes and frees place element but leaves NULL pointer in the place
bool List_remove(list *List, const unsigned int place);

//used on fractured queue to get it back formated
bool List_tidy(list *List);

//frees the list
bool List_destroy(list *List);