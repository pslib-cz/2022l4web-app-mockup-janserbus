#pragma once
#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef struct timespec timespec;

typedef struct{
    bool fire;
    timespec waitTime;
    timespec nextFire;
}Timer;

timespec timespecAdd(timespec a, timespec b);
timespec timespecDiff(timespec a, timespec b);

int timespecToInt_Sec(timespec time);
int timespecToInt_Milsec(timespec time);
double timespecToDouble(timespec time);

double deltaTime(timespec s, timespec e);

int Init_Timer(Timer *timer, int frequency);
void updateTimer(Timer *timer);

extern Timer Timer_frec10;






