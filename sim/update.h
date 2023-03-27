#include <time.h>
#include <stdbool.h>

typedef struct{
    double deltaTime;
    double deltaDuration;
    float fps;
    time_t starTime;
    time_t timeDuration;
}gameTime;

typedef struct{
    double popGrowth;    
    double popState;
    int popSize;
    bool running;
}gameInfo;

int Update(gameTime *gameTime, gameInfo *gameInfo);
