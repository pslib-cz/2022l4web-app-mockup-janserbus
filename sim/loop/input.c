#include <SDL2/SDL.h>

#include "../main.h"
#include "../engine.h"

int Input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            Game.running = false;
        }
    }
    
    return 0;
}