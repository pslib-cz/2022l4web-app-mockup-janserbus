#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"

int Input(gameTime *gameTime, gameInfo *gameInfo)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            gameInfo->running = false;
        }
    }
    
    return 0;
}
