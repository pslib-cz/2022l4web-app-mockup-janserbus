/**
 * PROCESSES
 * ==========================================================================
 */

#pragma once

#include "list.h"

typedef enum process{
    transition = 0
}process; 

typedef enum transitionType{
    linear = 0,
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

extern list Processes;

int translate(double *location, float endValue, float duration, transitionType mode);