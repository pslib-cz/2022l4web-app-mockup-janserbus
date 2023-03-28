#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "game.h"

int Draw(gameTime *gameTime, gameInfo *gameInfo, renderInfo *gameRend)
{
    char buffer[20];
    SDL_itoa(gameInfo->popSize, buffer, 10);
    SDL_Surface *surf = TTF_RenderText_Solid(gameRend->textFont, buffer , gameRend->textColor);
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

    SDL_RenderClear(gameRend->rend);

    SDL_RenderCopy(gameRend->rend, tex, NULL, NULL);
    SDL_RenderPresent(gameRend->rend);

    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);

    return 0;
}
