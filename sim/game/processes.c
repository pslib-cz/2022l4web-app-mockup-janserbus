#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>

#include "processes.h"
#include "data.h"


/**
 * QUEUE RELATED FUNCTIONS
 * ==========================================================================
 */

int initQueue(Queue *Queue){

    //mallocs space for 1 queue element
    Queue->queue = malloc(sizeof(void *));
    if(Queue->queue == NULL)
    {
        perror("Cannot initialize queue");
        return 1;
    }

    Queue->queue[0] = NULL;

    Queue->rear = -1;
    Queue->size = 1;

    return 0;
}

//returns position in the queue, in case of failure negative number
int enQueue(Queue *Queue, void *queueElement){

    //if invalid queue setup
    if(Queue->rear < -1 || Queue->size < 1)
    {
        errno = ERANGE;
        perror("Ivalid queue setup");
        return -1;
    }

    //if queue is too small
    if(Queue->rear + 1 >= Queue->size)
    {
        Queue->queue = realloc(Queue->queue, (Queue->size + 1) * sizeof(void *));
        Queue->size++;
    }

    Queue->queue[Queue->rear + 1] = queueElement;
    Queue->rear++;

    return Queue->rear;
}

//dequeues element in queue and adjuststs acordingly
int deQueue(Queue *Queue, unsigned int place){

    //check if request is outside of range
    if(place >= Queue->size)
    {
        errno = ERANGE;
        perror("invalid queue position");

        return 1;
    }
    //check if request is valid
    if(Queue->queue[place] == NULL)
    {
        return 0;
    }

    free(Queue->queue[place]);
    Queue->queue[place] = NULL;

    return 0;
}

//sorts queue to be withoutout empty spaceses and sets control variables
int tidyQueue(Queue *Queue){

    int swapPlace = -1;
    bool queueSorted = false;

    //possible to use Queue->rear + 1 to make algorithm more efficient
    for(int i = 0; i < Queue->size; i++)
    {
        if(queueSorted)
        {
            break;
        }

        if(Queue->queue[i] == NULL)
        {
            swapPlace = i;

            for(int j = swapPlace + 1; j < Queue->size; j++)
            {
                if(Queue->queue[j] != NULL)
                {
                    Queue->queue[swapPlace] = Queue->queue[j];
                    Queue->queue[j] = NULL;

                    break;
                }
            }

            queueSorted = true;            
        }
    }

    if(swapPlace == -1)
    {
        return 0;
    }

    Queue->rear = swapPlace - 1;

    return 0;
}

int clearQueue(Queue *Queue){

    for(int i = 0; i <= Queue->rear; i++)
    {
       free(&Queue->queue[i]);
    }

    free(Queue->queue);

    Queue->size = 0;
    Queue->rear = -1;    

    return 0;
}


/**
 * PROCESSES RELATED FUNCTIONS
 * ==========================================================================
 */

Queue Processes;

//adds process of given type into the queue
int createProcess(process type, ...){
    
    Process *proc = malloc(sizeof(Process)); //source

    va_list list;

    va_start(list, type);

    switch(type){

        case transition:

            proc->transition.type = transition;
            proc->transition.transitionType = va_arg(list, transitionType);
            proc->transition.location = va_arg(list, double *);
            proc->transition.startPoint = va_arg(list, double);
            proc->transition.endPoint = va_arg(list, double);
            proc->transition.duration = va_arg(list, double);

            if(enQueue(&Processes, proc) < 0)
            {
                errno = 1;
                perror("Enqueue falied");
            }

            break; 

        default:
            va_end(list);
            return 1;
    }

    va_end(list);
    return 0;
}

//is used to destroy process before its supposed end
int destroyProcess(unsigned int place){
    
    deQueue(&Processes ,place);

    //if last element return
    if(place == Processes.rear)
    {
        Processes.rear--;

        return 0;
    }
    //elif not last element, swap with the last element
    else if(place < Processes.rear)
    {
        Processes.queue[place] = Processes.queue[Processes.rear];
        Processes.queue[Processes.rear] = NULL;

        Processes.rear--;
    }

    return 0;
}

//loads curent process into the dest, returns 0 if all the processes were processed
//and returns place of the element processe in the queue as processPlace
int pollProcess(Process **dest, int *processPlace){

    static int processNumber = 0;

    //if end of the queue reached retun 0 and prepare for next interation
    if(Processes.rear < processNumber)
    {
        *processPlace = processNumber;
        *dest = NULL;
        processNumber = 0;
        return 1;
    }

    Process *cur = Processes.queue[processNumber];

    *processPlace = processNumber;
    *dest = cur;

    processNumber++;

    return 0;
}

//linear interpolation of location variable between its curent value and endValue in given duration
int translate(double *location, float endValue, float duration, transitionType mode){

    if(duration == 0)
    {
        errno = 1;
        perror("transition in zero time: ");

        return 1;
    }

    switch(mode)
    {
        case linear:
            float startValue = *location;
            createProcess(transition, mode, location, startValue, endValue, duration);
        break;

        case smooth:
        break;
    }

    return 0;
}