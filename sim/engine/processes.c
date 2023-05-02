/**
 * PROCESSES
 * ==========================================================================
 */

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "list.h"
#include "processes.h"

list Processes;

//adds process of given type into the queue
static int createProcess(process type, ...){
    
    Process *proc = malloc(sizeof(Process));

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

            List_append(&Processes, proc);

            break; 

        default:
            va_end(list);
            return 1;
    }

    va_end(list);
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