/**
 * DEFINITIONS OF LIST DATA TYPE (GENARAL PURPOSE DYNAMIC ARRAY)
 * ==========================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#include "list.h"
#include "processes.h"

list List_create(int size){
    
    list List;

    //mallocs space for size elements
    List.element = malloc(size * sizeof(void *));
    if(List.element == NULL)
    {
        printf("Cannot initialize List");
    }

    for(int i = 0; i < size; i++)
    {
        List.element[i] = NULL;
    }

    List.rear = -1;
    List.size = size;

    return List;
}

bool List_append(list *List, void *listElement){

    //if invalid list setup
    if(List->rear < -1 || List->size < 1)
    {
        errno = ERANGE;
        perror("Ivalid list setup");
        return false;
    }

    //if list is too small
    if(List->rear + 1 >= List->size)
    {
        List->element = realloc(List->element, (List->size + 4) * sizeof(void *));
        List->size += 4;
    }

    List->element[List->rear + 1] = listElement;
    List->rear++;

    return true;
}

bool List_remove(list *List, const unsigned int place){

    //check if request is outside of range
    if(place >= List->size)
    {
        errno = ERANGE;
        perror("Invalid list position");

        return false;
    }
    //check if request is valid
    if(List->element[place] == NULL)
    {
        printf("Using uninitialized list");
        return false;
    }

    free(List->element[place]);
    List->element[place] = NULL;

    return true;
}

void List_pop(list *List, const unsigned int place){

    List_remove(List, place);

    //if last element return
    if(place == List->rear)
    {
        List->element[place] = NULL;        
        List->rear--;

        return;
    }
    //elif not last element, swap with the last element
    else if(place < List->rear)
    {
        List->element[place] = List->element[List->rear];
        List->element[List->rear] = NULL;

        List->rear--;
    }

    return;
}


//sorts List to be withoutout empty spaceses and sets control variables
bool List_tidy(list *List){

    int swapPlace = -1;
    bool ListSorted = false;

    //TODO possible to use List->rear + 1 to make algorithm more efficient
    for(int i = 0; i < List->size; i++)
    {
        if(ListSorted)
        {
            break;
        }

        if(List->element[i] == NULL)
        {
            swapPlace = i;

            for(int j = swapPlace + 1; j < List->size; j++)
            {
                if(List->element[j] != NULL)
                {
                    List->element[swapPlace] = List->element[j];
                    List->element[j] = NULL;

                    break;
                }
            }

            ListSorted = true;            
        }
    }

    if(swapPlace == -1)
    {
        return true;
    }

    List->rear = swapPlace - 1;

    return true;
}

bool List_destroy(list *List){

    for(int i = 0; i <= List->rear; i++)
    {
       free(List->element[i]);
    }

    free(List->element);

    List->size = 0;
    List->rear = -1;    

    return true;
}