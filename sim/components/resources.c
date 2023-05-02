#include <stdio.h>

#include "../config.h"
#include "resources.h"

#define AMOUNT_OF_REASOURCE_TYPES 3

typedef struct storage{
    float amount;
    int cap;
}storage;

storage Storage[AMOUNT_OF_REASOURCE_TYPES];

void initReasources(void){

    Storage[food].amount = FOOD_START_AMOUNT;
    Storage[food].cap = FOOD_START_CAP;

    Storage[wood].amount = WOOD_START_AMOUNT;
    Storage[wood].cap = WOOD_START_CAP;

    Storage[stone].amount = STONE_START_AMOUNT;
    Storage[stone].cap = STONE_START_CAP;
}

//on succes returns amount of resource requested, else return zero float if resource unvailable
float getResource(resourceType type, float request){

    if(Storage[type].amount < request)
    {
        return 0;
    }

    if(request < 0 && request > AMOUNT_OF_REASOURCE_TYPES)
    {
        printf("Invalid resource type");
    }

    Storage[type].amount -= request;

    return request;
}

void createResource(resourceType type, float amount){

    if(Storage[type].cap < Storage[type].amount + amount)
    {
        return;
    }

    Storage[type].amount += amount;
}

void setResourceCap(resourceType type, int value){

    Storage[type].cap = value;
}

float resourceState(resourceType type){
    
    return Storage[type].amount;
}

int resourceCap(resourceType type){

    return Storage[type].cap;
}