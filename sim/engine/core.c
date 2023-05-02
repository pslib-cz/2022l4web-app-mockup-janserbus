/**
 * ENGINE CORE SETUP AND FUNCTIONS
 * ==========================================================================
 */


#include <stdlib.h>
#include <errno.h>

#include "../config.h"
#include "core.h"

game Game;

//initializing game data structures
int Game_init(){

    Game.running = true;
    Game.fps = 0;
    Game.frames = 0;

    Game.years = 0;
    Game.deltaTime = 0;
    Game.deltaDuration = 0;
    Game.duration = timeToTimespec(0);

    timespec_get(&Game.start, TIME_UTC);

    Game.window = SDL_CreateWindow("population", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!Game.window){
        printf("Error initializing GameData: %s\n", SDL_GetError());
        return 1;    
    }

    Game.renderer = SDL_CreateRenderer(Game.window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!Game.renderer){
        printf("Error initializing GameData: %s\n", SDL_GetError());
        SDL_DestroyWindow(Game.window);
        return 1;
    }

    Game.fontRoboto = TTF_OpenFont("fonts/Roboto.ttf", FONT_SIZE);
    if(!Game.fontRoboto){
        printf("Error initializing GameData: %s\n", TTF_GetError());
        SDL_DestroyRenderer(Game.renderer);
        SDL_DestroyWindow(Game.window);
        return 2;
    }

    Game.colorWite.r = 255;    
    Game.colorWite.g = 255;    
    Game.colorWite.b = 255;    
    Game.colorWite.a = 255;

    Game.colorRed.r = 255;    
    Game.colorRed.g = 0;    
    Game.colorRed.b = 0;    
    Game.colorRed.a = 255;

    return 0;
}

void Game_update(timespec *deltaStart, timespec *deltaStop){

    //sets corect timing for delta time and game duration
    timespec_get(deltaStop, TIME_UTC);
    Game.deltaTime = deltaTime(*deltaStart, *deltaStop);
    Game.duration = timespecDiff(*deltaStop, Game.start);
    timespec_get(deltaStart, TIME_UTC);

    //updates rest of the variables
    Game.fps = 1 / Game.deltaTime;
    Game.deltaDuration += Game.deltaTime;
    Game.years = Game.deltaDuration / YEAR_TIME;
    Game.frames++;
}

// genarates random number in range lower to upper inclusive
int randomNumber(int lower, int upper){

    int num = (rand() % (upper - lower + 1)) + lower;

    return num;
}