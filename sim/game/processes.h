#pragma once
#include <stdio.h>
#include <time.h>

#include "time.h"

typedef enum process{
    transition
}process; 

typedef enum transitionType{
    linear,
    smooth
}transitionType;

typedef struct Transition{
    process type;
    transitionType transitionType;
    double *location;
    float startPoint;
    float endPoint;
    float duration;
}Transition;

typedef union Process{
    process type;
    Transition transition;
}Process;

/**
 * General queue functions and data structures
 * ==========================================================================
 */

typedef struct Queue{
    void **queue;
    int size;
    int rear;
}Queue;

int initQueue(Queue *Queue);
int enQueue(Queue *Queue, void *queueElement);
int deQueue(Queue *Queue, unsigned int place);
int tidyQueue(Queue *Queue);
int clearQueue(Queue *Queue);


/**
 * Processes related functions and variables
 * ==========================================================================
 */

extern Queue Processes;

int createProcess(process type, ...);
int destroyProcess(unsigned int place);
int pollProcess(Process **dest, int *processPlace);

int translate(double *location, float endValue, float duration, transitionType mode);

