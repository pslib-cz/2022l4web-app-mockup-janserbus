#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "game.h"

int RenderText(char *label, renderInfo *gameRend, int xPos, int yPos);

int Draw(gameTime *gameTime, gameInfo *gameInfo, renderInfo *gameRend)
{
    SDL_RenderClear(gameRend->rend);

    char *buffer = malloc(20 * sizeof(char));

    sprintf(buffer, "population: %i", gameInfo->popSize);
    RenderText(buffer, gameRend, SCREEN_PADDING, SCREEN_PADDING);

    sprintf(buffer, "years: %li", gameTime->timeDuration);
    RenderText(buffer, gameRend, SCREEN_PADDING, SCREEN_PADDING + LINE_HEIGHT + FONT_SIZE);

    sprintf(buffer, "fps: %f", gameTime->fps);
    RenderText(buffer, gameRend, SCREEN_PADDING, SCREEN_PADDING + 2 * LINE_HEIGHT + FONT_SIZE);

    SDL_RenderPresent(gameRend->rend);

    return 0;
}

int RenderText(char *label, renderInfo *gameRend, int xPos, int yPos){

    SDL_Surface *surf = TTF_RenderText_Blended(gameRend->textFont, label , gameRend->textColor);
    if(!surf){
        printf("Error creating surface: %s\n", SDL_GetError());
        return 1;
    }    

    SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRend->rend, surf);
    if(!tex){
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        return 1;
    }

    SDL_FreeSurface(surf);

    SDL_Rect posInfo = {xPos, yPos, surf->w, surf->h};

    posInfo.w = posInfo.w * FONT_SIZE / posInfo.h;
    posInfo.h = FONT_SIZE;   

    SDL_RenderCopy(gameRend->rend, tex, NULL, &posInfo);

    return 0;
}