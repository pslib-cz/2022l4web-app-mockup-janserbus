#include <stdio.h>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <unistd.h>

#include "game.h"

void initializeGameInfo(gameInfo *game, double pop_growth, double pop_state, int pop_size);
void initializeGameTime(gameTime *time_info, double delta_time);
int initializerenderInfo(renderInfo *gameRend);


int main(int argc, char *argv[]){

    if(argc != 3)
    {
        printf("Usage: ./pop starting_population pop_growth\n");
        return 1;
    }

    //initializing game date structures
    gameInfo gameInfo;
    gameTime gameTime;
    renderInfo gameRend;

    //initialzing SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    
    if(TTF_Init() != 0){
        printf("Error initializing TTF extension: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }


    initializeGameInfo(&gameInfo, atof(argv[2]), atof(argv[1]), atoi(argv[1]));
    initializeGameTime(&gameTime, 0);    
    if(initializerenderInfo(&gameRend) != 0){
        return 1;
    }

    struct timespec deltaStart, deltaStop; 
    struct timespec framecapStart, framecapStop; 

    timespec_get(&deltaStart, TIME_UTC);

    while(gameInfo.running)
    {   
        timespec_get(&framecapStart, TIME_UTC);

        Input(&gameTime, &gameInfo);        
        Update(&gameTime, &gameInfo);

        if(Draw(&gameTime, &gameInfo, &gameRend) != 0)
        {
            SDL_DestroyRenderer(gameRend.rend);
            SDL_DestroyWindow(gameRend.win);    
            TTF_CloseFont(gameRend.textFont);
            TTF_Quit();
            SDL_Quit();
            return 1;
        }
        
        timespec_get(&framecapStop, TIME_UTC);

        //wait in order to maintain framerate
        SDL_Delay((int) (1 / FRAME_CAP - DeltaTime(framecapStart, framecapStop)) * 1000);

        timespec_get(&deltaStop, TIME_UTC);
        gameTime.deltaTime = DeltaTime(deltaStart, deltaStop);
        timespec_get(&deltaStart, TIME_UTC);
    }

    SDL_DestroyRenderer(gameRend.rend);
    SDL_DestroyWindow(gameRend.win);    
    TTF_CloseFont(gameRend.textFont);
    TTF_Quit();
    SDL_Quit();
}

void initializeGameInfo(gameInfo *game, double pop_growth, double pop_state, int pop_size){
    game->popGrowth = pop_growth;
    game->popSize = pop_size;
    game->popState = pop_state;
    game->running = true;
}

void initializeGameTime(gameTime *time_info, double delta_time){
    time_info->deltaTime = delta_time;
    time_info->starTime = time(NULL);
    time_info->timeDuration = 0;
    time_info->deltaDuration = 0;
    time_info->fps = 0;
}
int initializerenderInfo(renderInfo *gameRend){

    gameRend->win = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!gameRend->win){
        printf("Error creating window: %s\n", SDL_GetError());    
        TTF_Quit();
        SDL_Quit();
        return 1;    
    }

    gameRend->rend = SDL_CreateRenderer(gameRend->win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!gameRend->rend){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(gameRend->win);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    gameRend->textFont = TTF_OpenFont("fonts/Roboto-Regular.ttf", 1000);
    if(!gameRend->textFont){
        printf("Error initializing font: %s", TTF_GetError());
        SDL_DestroyRenderer(gameRend->rend);
        SDL_DestroyWindow(gameRend->win);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    gameRend->textColor.r = 255;    
    gameRend->textColor.g = 255;    
    gameRend->textColor.b = 255;    
    gameRend->textColor.a = 0;

    return 0;
}


double DeltaTime(struct timespec s, struct timespec e)
{
    return ((e.tv_sec * 1000000000 + e.tv_nsec) - (s.tv_sec * 1000000000 + s.tv_nsec)) / 1000000000.0;
}