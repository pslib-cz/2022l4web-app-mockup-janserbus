/**
 * TIME FUNCTIONALITY
 * ==========================================================================
 */

#pragma once

#include <time.h>

typedef struct timespec timespec;

typedef struct{
    bool fire;
    timespec waitTime;
    timespec nextFire;
}Timer;

timespec timespecAdd(timespec a, timespec b);
timespec timespecDiff(timespec a, timespec b);
timespec timeToTimespec(double time);

int timespecToInt_Sec(timespec time);
int timespecToInt_Milsec(timespec time);
double timespecToDouble(timespec time);
void doubleToTimespec(timespec *location, double source);

double deltaTime(timespec s, timespec e);

int Init_Timer(Timer *timer, float frequency);
void updateTimer(Timer *timer);

extern Timer Timer_graph;
extern Timer Timer_frec1;