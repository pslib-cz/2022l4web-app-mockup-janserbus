#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "time.h"
#include "data.h"

Timer Timer_frec10;


//Timer functions
int Init_Timer(Timer *timer, int frequency){
    double time = 1.0 / frequency;

    long sec =  round(time);
    long nsec =  round((time - sec) * 1000);

    timer->waitTime.tv_sec = sec;
    timer->waitTime.tv_nsec = nsec * 1000000;

    timer->nextFire = timespecAdd(Game.duration, timer->waitTime);

    timer->fire = true;
    
    return 0;
}

void updateTimer(Timer *timer){    

    timer->fire = false;

    long fire = timespecToInt_Milsec(timer->nextFire);
    long duration = timespecToInt_Milsec(Game.duration);

    if( fire <= duration){
        timer->fire = true;
        timer->nextFire = timespecAdd(Game.duration, timer->waitTime);
    }

    return;
}

double deltaTime(timespec s, timespec e)
{
    return timespecToDouble(timespecDiff(e, s));
}


//timespec arithmetics
timespec timespecDiff(timespec a, timespec b){

    timespec temp;

    long nsec_diference = a.tv_nsec - b.tv_nsec;
    long sec_diference = a.tv_sec - b.tv_sec;

    if((nsec_diference < 0 && sec_diference >= 0) || (nsec_diference >= 0 && sec_diference < 0)){
        temp.tv_sec = abs(sec_diference) - 1;
        temp.tv_nsec = 1000000000 - abs(nsec_diference);
        return temp;
    }

    temp.tv_sec = abs(sec_diference);
    temp.tv_nsec = abs(nsec_diference);

    return temp;
}
timespec timespecAdd(timespec a, timespec b){

    timespec temp;

    long sec_sum = a.tv_sec + b.tv_sec;
    long nsec_sum = a.tv_nsec + b.tv_nsec;

    if(nsec_sum > 999999999){
        sec_sum++;
        nsec_sum = nsec_sum - 1000000000;
    }

    temp.tv_sec = sec_sum;
    temp.tv_nsec = nsec_sum;

    return temp;
}

//Timespec conversino functions
int timespecToInt_Sec(timespec time)
{
    return round((time.tv_sec * 1000000000 + time.tv_nsec) / 1000000000.0);
}
int timespecToInt_Milsec(timespec time)
{
    return round((time.tv_sec * 1000000000 + time.tv_nsec) / 1000000.0);
}
double timespecToDouble(timespec time)
{
    return (time.tv_sec * 1000000000 + time.tv_nsec) / 1000000000.0;
}