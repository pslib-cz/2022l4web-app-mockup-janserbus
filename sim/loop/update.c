#include <stdio.h>
#include <math.h>

#include "../config.h"
#include "../main.h"
#include "../components/population.h"
#include "../components/resources.h"
#include "../engine.h"

void growPopulation();
void populationEat();

int Update(){

    createResource(food, FOOD_RATE * Game.deltaTime);

    populationEat();

    for(int i = 0; i < Population.size; i++)
    {
        Person_update(i);
    }

    growPopulation();    

    printPopulationData();

    updatePopulation();

    if(Timer_graph_sampling.fire)
    {
        Data_addPoint(&PopulationData, timespecToDouble(Game.duration), Population.state);
    }

    return 0;
}

double growthCoefficient(void);
void growPopulation(){

    Population.growth = POP_GROWTH / YEAR_TIME * growthCoefficient();

    int lastPopSize = Population.state;
    
    Population.state = Population.state * exp(Population.growth * Game.deltaTime);
    Population.size = trunc(Population.state);
        
    int popDelta =  Population.size - lastPopSize;

    //change amount of population acordingly
    if(popDelta > 0)
    {
        for(int i = 0; i < popDelta; i++)
        {
            Person_create();
        }
    }
    else if(popDelta < 0)
    {
        for(int i = 0; i < abs(popDelta); i++)
        {
            Person_kill(randomNumber(0, Population.size - 1 - i));
        }        
    }
}

double growthCoefficient(void){

    if(Population.averageHappiness > 80.0)
    {
        return 1;
    }
    else if(Population.averageHappiness < 0.0)
    {
        return -1;
    }
    else
    {
        return 0.025 * Population.averageHappiness - 1;
    }
}

void populationEat(){
    int places[Population.size];

    for(int i = 0; i < Population.size; i++)
    {
        places[i] = i;        
    }

    int feed = -1;

    for(int i = 0; i < Population.size; i++)
    {
        int temp = -1;

        feed = randomNumber(0, Population.size - 1 - i);

        Person_eat(places[feed]);

        temp = places[Population.size - 1 - i];
        places[Population.size - 1 - i] = places[feed];
        places[feed] = temp;
    }
}