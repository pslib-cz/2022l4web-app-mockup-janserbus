#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "../game/data.h"

int RenderText(SDL_Renderer *rend, char *label, TTF_Font *font, SDL_Color color, int xPos, int yPos);
int row(int);

int Draw(){

    SDL_RenderClear(Game.renderer);

    char *buffer = malloc(40 * sizeof(char));

    sprintf(buffer, "population1: %li", Population1.size);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(0));

    sprintf(buffer, "population2: %li", Population2.size);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorRed, SCREEN_PADDING, row(1));

    sprintf(buffer, "fps: %i", (int) Game.fps);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, 1180, row(0));    

    sprintf(buffer, "years: %i", (int) timespecToInt_Sec(Game.duration));
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(2));

    sprintf(buffer, "delta: %f", Game.deltaDuration);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(3));

    if(Timer_frec10.fire){
        RenderText(Game.renderer, "timer", Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(4));
    }

    free(buffer);

    RenderGraph(Game.renderer, MainGraph, Game.colorWite);

    RenderGraphData(Game.renderer, MainGraph, Data1, Game.colorWite);
    RenderGraphData(Game.renderer, MainGraph, Data2, Game.colorRed);

    SDL_RenderPresent(Game.renderer);

    return 0;
}

int RenderText(SDL_Renderer *rend, char *label, TTF_Font *font, SDL_Color color, int xPos, int yPos){

    SDL_Surface *surf = TTF_RenderText_Blended(font, label, color);
    if(!surf){
        printf("Error creating surface: %s\n", SDL_GetError());
        return 1;
    }    

    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game.renderer, surf);
    if(!tex){
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        return 1;
    }

    SDL_FreeSurface(surf);

    SDL_Rect posInfo = {xPos, yPos, surf->w, surf->h};

    posInfo.w = posInfo.w * FONT_SIZE / posInfo.h;
    posInfo.h = FONT_SIZE;   

    SDL_RenderCopy(Game.renderer, tex, NULL, &posInfo);

    SDL_DestroyTexture(tex);

    return 0;
}

int row(int rowNumber){
    if (rowNumber == 0)
    {
        return SCREEN_PADDING;
    }    

    return SCREEN_PADDING + LINE_HEIGHT * rowNumber + FONT_SIZE * rowNumber;    
}