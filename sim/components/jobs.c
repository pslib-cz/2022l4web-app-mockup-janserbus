#include <stdio.h>
#include "jobs.h"

#include "../config.h"
#include "resources.h"
#include "population.h"
#include "../game/processes.h"

typedef struct resource{
    float amount;
    resourceType type;
}resource;

typedef struct job{
    int inputsAmount;
    int outputsAmount;
    resource *inputPerWorker;
    resource *outputPerWorker;
    int workersCap;
    int workersAmount;
    Queue workers;
}job;

job Jobs[AMOUNT_OF_JOB_TYPES];

static void initJob(jobTypes type, float output, resourceType outputType, int inputAmount, resource *inputs, int startCap);

void initJobs(){

    initJob(foodGatherer, 0.05, food, 0, NULL, CAP_UNLIMITED);

    initJob(woodGatherer, 0.2, wood, 0, NULL, CAP_UNLIMITED);

    initJob(stoneGatherer, 0.1, stone, 0, NULL, CAP_UNLIMITED);
}
void Job_update(void){


}

void freeJobs(void){

    for(int i = 0; i < AMOUNT_OF_JOB_TYPES; i++)
    {
        if(Jobs[i].inputsPerWorker != NULL)
        {
            free(Jobs[i].inputsPerWorker);
        }

        clearQueue(&Jobs[i].workers);        
    }    
}

void assignWorker(jobTypes type){

    if(Jobs[type])

    
}

/*TODO list
    assignWorker();
    romoveWorker();
    changeJobsCap();
    createOutput();
*/

static void initJob(jobTypes type, resource *inputs, int inputsAmount,resource *outputs, int outputsAmount, int startCap){

    Jobs[type].inputsAmount = inputsAmount;
    Jobs[type].outputsAmount = outputsAmount;
    Jobs[type].inputPerWorker = inputs;
    Jobs[type].outputPerWorker = outputs;

    

    initQueue(&Jobs[type].workers, 5);
}