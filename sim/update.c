#include <stdio.h>
#include <math.h>
#include <time.h>

#include "game.h"

#define e 2.7182818

int growPopulation(double start, double growth, double time, double *popState);
void printInfo();


int Update(gameTime *gameTime, gameInfo *gameInfo){

    gameInfo->popSize = growPopulation(gameInfo->popState, gameInfo->popGrowth, gameTime->deltaTime, &gameInfo->popState);
    
    gameTime->timeDuration = time(NULL) - gameTime->starTime;
    gameTime->deltaDuration += gameTime->deltaTime;
    gameTime->fps = 1 / gameTime->deltaTime;

    return 0;
}

int growPopulation(double start, double growth, double time, double *popState)
{
    *popState = start * pow(e, growth * time);

    return floor(*popState);
}