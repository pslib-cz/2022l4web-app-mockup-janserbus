#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "update.h"

int growPopulation(double start, double growth, double time, double *popState);
void printInfo();


int Update(gameTime *gameTime, gameInfo *gameInfo){

    gameInfo->popSize = growPopulation(gameInfo->popState, gameInfo->popGrowth, gameTime->deltaTime, &gameInfo->popState);
    
    gameTime->timeDuration = time(NULL) - gameTime->starTime;
    gameTime->deltaDuration += gameTime->deltaTime;
    gameTime->fps = 1 / gameTime->deltaTime;

    printInfo(*gameInfo, *gameTime);
    return 0;
}

int growPopulation(double start, double growth, double time, double *popState)
{
    const double e = 2.7182818;

    *popState = start * pow(e, growth * time);

    return floor(*popState);
}

void printInfo(gameInfo game, gameTime t){    
    
    printf("\rPopulation size: %i; Time: %li; Fps: %f", game.popSize, t.timeDuration, t.fps);
}