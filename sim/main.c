#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#include "config.h"
#include "main.h"
#include "engine.h"
#include "components.h"

int Engine_init();
int QuitGame();
int Processing();

int main(void){

    SDL_SetMainReady();

    Engine_init();

    timespec deltaStart, deltaStop, frameCapStart, frameCapStop; 

    timespec_get(&deltaStart, TIME_UTC);

    while(Game.running)
    {   
        timespec_get(&frameCapStart, TIME_UTC);

        Input(); 

        Update();

        if(Draw() != 0)
        {
            QuitGame();

            return 1;
        }

        Processing();

        updateTimer(&Timer_graph_sampling);
        updateTimer(&Timer_frec1);
        
        timespec_get(&frameCapStop, TIME_UTC);

        //delay to keep frame cap
        int wait = (1.0 / FRAME_CAP - deltaTime(frameCapStart, frameCapStop)) * 1000;
        if(wait > 0)
        {
            SDL_Delay(wait);
        }

        //update game data for next frame
        Game_update(&deltaStart, &deltaStop);        
    }
    
    QuitGame();

    return 0;
}

int QuitGame(void){

    List_destroy(&Processes);
    clearPopulation();
    
    free(PopulationData.points);

    SDL_DestroyRenderer(Game.renderer);
    SDL_DestroyWindow(Game.window);    
    TTF_CloseFont(Game.fontRoboto);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

int Processing(){

    for(int i = 0; i < Processes.rear + 1; i++)
    {
        Process *process = Processes.element[i];

        switch(process->type)
        {
            case(transition):
                if(process->transition.transitionType == linear)
                {
                    //return transition value
                    *process->transition.location += (Game.deltaTime / process->transition.duration) * (process->transition.endPoint - process->transition.startPoint);

                    //if transition ended terminate process
                    if(process->transition.endPoint > process->transition.startPoint && *process->transition.location >= process->transition.endPoint)
                    {
                        *process->transition.location = process->transition.endPoint;
                        List_remove(&Processes, i);
                    }
                    else if(process->transition.endPoint < process->transition.startPoint && *process->transition.location <= process->transition.endPoint)
                    {
                        *process->transition.location = process->transition.endPoint;
                        List_remove(&Processes, i);
                    }
                }
                else if(process->transition.transitionType == smooth)
                {
                    List_remove(&Processes, i);
                }

            break;
        }
    };

    return 0;
}

int Engine_init(){

    errno = 0;

    //seed for random number generation
    srand(time(0));

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
    if(Game_init() != 0){
        SDL_Quit();
        TTF_Quit();
    }      

    Processes = List_create(4);

    Init_Timer(&Timer_graph_sampling, GRAPH_SAMPLING);
    Init_Timer(&Timer_frec1, 1);

    initPopulation();    

    initReasources();

    SDL_Point origin;

    origin.x = SCREEN_WIDTH - SCREEN_PADDING - 500;
    origin.y = SCREEN_PADDING;

    Graph_init(&PopulationGraph, origin, 350, 1, 0.1, 0, 0, "sec", "pop size");

    return 0;
}