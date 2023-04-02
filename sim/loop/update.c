#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../game/data.h"

#define e 2.7182818

void growPopulation(Population *population);

int Update(){

    growPopulation(&Population1);
    growPopulation(&Population2);

    if(Timer_frec10.fire){

        addDataPoint(&Data1, timespecToDouble(Game.duration), Population1.size);
        addDataPoint(&Data2, timespecToDouble(Game.duration), Population2.size);
    }

    return 0;
}

void growPopulation(Population *population){

    population->state = population->state * pow(e, population->growth * Game.deltaTime);
    population->size = floor(population->state);

    return;
}