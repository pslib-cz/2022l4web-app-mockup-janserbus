#include <SDL2/SDL.h>

#include "../main.h"
#include "../engine.h"

void keyDownEvent(const SDL_KeyboardEvent keyEvent);

int Input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Game.running = false;
                break;
            
            //handel key presses
            case SDL_KEYDOWN:
                keyDownEvent(event.key);
                break;
                     
            default:
                break;
        }
    }
    
    return 0;
}

void keyDownEvent(const SDL_KeyboardEvent keyEvent){

    int ints = 0;

    const Uint8 *keystate = SDL_GetKeyboardState(&ints);

    if(keystate[SDLK_LSHIFT] && ints > SDLK_LSHIFT)
    {
        printf("SHIFT engaded\n");
    }

    switch(keyEvent.keysym.mod)
    {
        case KMOD_LSHIFT:

            printf("CTRL\n");
            break;
        
        case KMOD_LCTRL:
            printf("SHIFT\n");
        break;

        default:
            break;
    }    

}