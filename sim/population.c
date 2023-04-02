#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <time.h>

#include "game/data.h"

int main(void){

    SDL_SetMainReady();

    //initialzing SDL and TTF libraries
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }    
    if(TTF_Init() != 0){
        printf("Error initializing TTF extension: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //init game data structures
    if(Init_GameData() != 0){
        SDL_Quit();
        TTF_Quit();
    }      

    //Timer struct initialization
    Init_Timer(&Timer_frec10, 1);

    Init_Population(&Population1, "pop1", 100, 0.08);    
    Init_Population(&Population2, "pop2", 400, 0.02);    

    Init_Graph(&MainGraph, 650, 480, SCREEN_PADDING, 10, 0.1);

    timespec deltaStart, deltaStop; 
    timespec framecapStart, framecapStop; 

    timespec_get(&deltaStart, TIME_UTC);

    while(Game.running)
    {   
        timespec_get(&framecapStart, TIME_UTC);


        Input();        
        Update();
        if(Draw() != 0)
        {
            SDL_DestroyRenderer(Game.renderer);
            SDL_DestroyWindow(Game.window);    
            TTF_CloseFont(Game.fontRoboto);
            TTF_Quit();
            SDL_Quit();
            return 1;
        }
        
        timespec_get(&framecapStop, TIME_UTC);

        //wait in order to maintain framerate
        SDL_Delay(round(1 / FRAME_CAP - deltaTime(framecapStart, framecapStop)) * 1000);

        timespec_get(&deltaStop, TIME_UTC);
        Game.deltaTime = deltaTime(deltaStart, deltaStop);
        Game.duration = timespecDiff(deltaStop, Game.start);
        timespec_get(&deltaStart, TIME_UTC);

        //GameUpdate

        updateTimer(&Timer_frec10);

        Game.deltaDuration += Game.deltaTime;
        Game.fps = 1 / Game.deltaTime;
    }
    
    SDL_DestroyRenderer(Game.renderer);
    SDL_DestroyWindow(Game.window);    
    TTF_CloseFont(Game.fontRoboto);
    TTF_Quit();
    SDL_Quit();
}