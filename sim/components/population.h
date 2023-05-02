#pragma once
#include <stdbool.h>

#include "jobs.h"
#include "stdio.h"

typedef struct person{
    float happiness;
    float hunger;
    jobTypes job;
    bool housing;
}person;

typedef struct populationData{
    double state;
    int size;
    double growth;
    float averageHunger;
    float averageHappiness;
}populationData;

int initPopulation(void);
int clearPopulation(void);
void updatePopulation(void);
void printPopulationData(void);


person *Person_get(unsigned int place);
void Person_create(void);
void Person_kill(unsigned int place);
void Person_eat(unsigned int place);
void Person_update(unsigned int place);
void Person_print(unsigned int place, FILE *stream);

extern populationData Population;