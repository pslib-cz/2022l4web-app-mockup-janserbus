#include <math.h>

#include "../config.h"
#include "../engine.h"
#include "population.h"
#include "resources.h"

populationData Population;

list Pop;

//initialize population queue
int initPopulation(){

    Pop = List_create(POP_START_SIZE);

    for(int i = 0; i < POP_START_SIZE; i++)
    {
        Person_create();
    }

    Population.state = POP_START_SIZE;
    Population.size = POP_START_SIZE;
    Population.growth = POP_GROWTH / YEAR_TIME;
    Population.averageHunger = 0;
    Population.averageHappiness = 0;

    return 0;
}

void updatePopulation(void){

    person *Person;

    float happinessSum = 0;
    float hungerSum = 0;

    for(int i = 0; i < Population.size; i++)
    {
        Person = Pop.element[i];

        hungerSum += Person->hunger;
        happinessSum += Person->happiness;
    }

    Population.averageHunger = hungerSum / Population.size;
    Population.averageHappiness = happinessSum / Population.size;
}

void printPopulationData(void){

    static bool opend = false;

    FILE *outfile;

    if(opend)
    {
        outfile = fopen("data.txt", "a");
    }
    else
    {
        opend = true;
        outfile = fopen("data.txt", "w");
    }


    fprintf(outfile, "\n\n\nFrame: %li\n", Game.frames);
    fprintf(outfile, "Delta Time: %.2f\n", Game.deltaTime);
    fprintf(outfile, "Average hunger: %.2f\n", Population.averageHunger);
    fprintf(outfile, "Average happiness: %.2f\n", Population.averageHappiness);
    fprintf(outfile, "Pop size: %i\n", Population.size);
    fprintf(outfile, "Pop queue size: %i\n", Population.size);
    fprintf(outfile, "\n---------------------------\n");

    for(int i = 0; i < Pop.rear + 1; i++)
    {
        Person_print(i, outfile);
    }    

    fclose(outfile);
}

int clearPopulation(void){

    List_destroy(&Pop);

    return 0;
}

//Person struct functions
void Person_create(void){

    person *Person = malloc(sizeof(person));

    Person->happiness = INIT_HAPPINESS;
    Person->hunger = INIT_HUNGER;
    Person->housing = false;
    Person->job = none;

    List_append(&Pop, Person);

    return;
}

person *Person_get(unsigned int place){
    
    //return if outside of queue
    if(place > Pop.rear)
    {
        return NULL;
    }

    person *pop;

    pop = Pop.element[place];

    return pop;
}


//kills one person
void Person_kill(unsigned int place){

    List_pop(&Pop, place);
}

void Person_eat(unsigned int place){

    //return if outside of queue
    if(place > Pop.rear)
    {
        return;
    }

    person *Person = Pop.element[place];
    
    //condition to regain
    if(Person->hunger < 90 && Timer_frec1.fire)
    {
       Person->hunger += FOOD_TO_HUNGER * getResource(food, FEED_RATE * randomNumber(1, 10));
    }
}

//called every frame
void Person_update(unsigned int place){

    //return if outside of queue
    if(place > Pop.rear)
    {
        return;
    }

    person *Person = Pop.element[place];

    //hunger update
    Person->hunger = -HUNGER_RATE * Game.deltaTime + Person->hunger;

    if(Person->hunger < 0.0001)
    {
        Person->hunger = 0;
    }

    //happinness update

    Person->happiness = (Person->hunger * 0.8) + (Person->housing * 10) + ((Person->job > -1 ? 1 : 0) * 10);
}

void Person_print(unsigned int place, FILE *stream){

    person *Person = Pop.element[place];

    fprintf(stream, "\nPerson[%i]\n", place);
    fprintf(stream, "  happiness: %.0f\n", Person->happiness);
    fprintf(stream, "     hunger: %.0f\n", Person->hunger);
    fprintf(stream, "  jobStatus: %s\n", Person->job > -1 ? "employed" : "unemployed");
    fprintf(stream, "    housing: %s\n", Person->housing ? "true" : "false");
}