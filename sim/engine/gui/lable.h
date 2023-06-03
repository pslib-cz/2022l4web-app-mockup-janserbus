#pragma once

#include <SDL2/SDL_ttf.h>

#define MAX_LABLE_LENGTH 20

typedef struct lable{
    char lable[MAX_LABLE_LENGTH];
    SDL_Point origin;
    int size;
    TTF_Font *font;
}lable;

