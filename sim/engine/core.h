
/**
 * ENGINE CORE SETUP AND FUNCTIONS
 * ==========================================================================
 */

# pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdbool.h>

#include "time.h"

typedef struct{
    bool running;
    float fps;
    double deltaTime;
    double deltaDuration;
    int years;
    long frames;
    timespec duration;
    timespec start;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *fontRoboto;
    SDL_Color colorWite;
    SDL_Color colorRed;
}game;

int Game_init();
void Game_update(timespec *deltaStart, timespec *deltaStop);

int randomNumber(int lower, int upper);

//get initialize game structures to use globaly
extern game Game;