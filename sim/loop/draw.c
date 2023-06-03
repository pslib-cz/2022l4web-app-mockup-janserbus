#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>


#include "../config.h"
#include "../main.h"
#include "../components/population.h"
#include "../components/resources.h"

#include "../engine.h"


int RenderText(SDL_Renderer *rend, char *label, TTF_Font *font, SDL_Color color, int xPos, int yPos);
int row(int);

int Draw(){

    SDL_RenderClear(Game.renderer);

    char *buffer = malloc(40 * sizeof(char));

    sprintf(buffer, "population: %.2f", Population.state);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(0)); 

    sprintf(buffer, "years: %i", Game.years);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, 1180, row(0));

    sprintf(buffer, "growth: %f", Population.growth * YEAR_TIME);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(1));

    sprintf(buffer, "food: %.2f", resourceState(food));
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(2));

    sprintf(buffer, "wood: %.2f", resourceState(wood));
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(3));

    sprintf(buffer, "stone: %.2f", resourceState(stone));
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(4));

    sprintf(buffer, "average hunger: %.2f", Population.averageHunger);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(5));

    sprintf(buffer, "average happinness: %.2f", Population.averageHappiness);
    RenderText(Game.renderer, buffer, Game.fontRoboto, Game.colorWite, SCREEN_PADDING, row(6));

    free(buffer);

    Graph_render(Game.renderer, PopulationGraph, Game.colorWite);

    RenderGraphData(Game.renderer, PopulationGraph, PopulationData, Game.colorWite);    

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

    SDL_Rect posInfo = {xPos, yPos, surf->w, surf->h};

    posInfo.w = posInfo.w * FONT_SIZE / posInfo.h;
    posInfo.h = FONT_SIZE;

    SDL_FreeSurface(surf);

    SDL_RenderCopy(Game.renderer, tex, NULL, &posInfo);

    SDL_DestroyTexture(tex);

    return 0;
}

int row(int rowNumber){

    return SCREEN_PADDING + LINE_HEIGHT * rowNumber + FONT_SIZE * rowNumber;    
}