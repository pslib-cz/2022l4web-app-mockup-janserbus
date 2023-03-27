#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include "update.h"

double DeltaTime();
int initializeGameInfo(gameInfo *game, double pop_growth, double pop_state, int pop_size);
int initializeGameTime(gameTime *time_info, double delta_time);

int main(int argc, char *argv[]){
    if(argc != 3)
    {
        printf("Usage: ./pop starting_population pop_growth");
        return 1;
    }

    gameInfo gameInfo;
    gameTime gameTime;

    initializeGameInfo(&gameInfo, atof(argv[2]), atof(argv[1]), atoi(argv[1]));
    initializeGameTime(&gameTime, 0);

    struct timespec start, stop;
    // struct timespec delay, rem;
    // delay.tv_sec = 0;
    // delay.tv_nsec = 10000000;


    timespec_get(&start, TIME_UTC);

    while(gameInfo.running)
    {   
        //Input();
        // nanosleep(&delay, &rem);
        Update(&gameTime, &gameInfo);
        //Draw();

        if( 300 <= gameTime.timeDuration)
        {
            break;
        }

        timespec_get(&stop, TIME_UTC);
        gameTime.deltaTime = DeltaTime(start, stop);
        timespec_get(&start, TIME_UTC);
    }
       
}

int initializeGameInfo(gameInfo *game, double pop_growth, double pop_state, int pop_size){
    game->popGrowth = pop_growth;
    game->popSize = pop_size;
    game->popState = pop_state;
    game->running = true;

    return 0;
}
int initializeGameTime(gameTime *time_info, double delta_time){
    time_info->deltaTime = delta_time;
    time_info->starTime = time(NULL);
    time_info->timeDuration = 0;
    time_info->deltaDuration = 0;
    time_info->fps = 0;

    return 0;
}
double DeltaTime(struct timespec s, struct timespec e)
{
    return ((e.tv_sec * 1000000000 + e.tv_nsec) - (s.tv_sec * 1000000000 + s.tv_nsec)) / 1000000000.0;
}