#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../game/data.h"
#include "../game/processes.h"

#define e 2.7182818
#define CARY_CAP 300
#define INIT 10

void growPopulation_Log(Population *population);
void growPopulation_Exp(Population *population);


int Update(){

    static bool fire1 = true;
    static bool fire2 = true;
    static bool fire3 = true;
    static bool fire4 = true;

    if(timespecToInt_Sec(Game.duration) > 10 && fire1)
    {
        translate(&Population1.growth, -0.01, 20, linear);
        fire1 = false;
    }
    if(timespecToInt_Sec(Game.duration) > 5 && fire2)
    {
        translate(&Population2.growth, 0.2, 10, linear);
        fire2 = false;
    }
    if(timespecToInt_Sec(Game.duration) > 20 && fire3)
    {
        translate(&Population2.growth, -0.05, 20, linear);
        fire3 = false;
    }
    if(timespecToInt_Sec(Game.duration) > 1 && fire4)
    {
        translate(&Population2.growth, -0.05, 20, smooth);
        fire4 = false;
    }

    growPopulation_Exp(&Population1);
    growPopulation_Exp(&Population2);

    if(Timer_frec10.fire){

        addDataPoint(&Data1, timespecToDouble(Game.duration), Population1.size);
        addDataPoint(&Data2, timespecToDouble(Game.duration), Population2.size);
    }

    return 0;
}

//Logistic growth function
void growPopulation_Log(Population *population){

    population->state = CARY_CAP / (1 + INIT * pow(e, -population->growth * (timespecToDouble(Game.duration) - 40)));
    population->size = floor(population->state);

    return;
}

//Exponential growth function
void growPopulation_Exp(Population *population){

    population->state = population->state * pow(e, population->growth * Game.deltaTime);
    population->size = floor(population->state);

    return;
}