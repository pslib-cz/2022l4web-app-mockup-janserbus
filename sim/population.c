#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#include "game/time.h"
#include "game/data.h"
#include "game/processes.h"

int QuitGame(void);
int Processing();


int main(void){

    errno = 0;

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

    initQueue(&Processes);

    //Timer struct initialization
    Init_Timer(&Timer_frec10, 1);

    Init_Population(&Population1, "pop1", 100, 0.05);    
    Init_Population(&Population2, "pop2", 10, 0.1);    

    Init_Graph(&MainGraph, 650, 480, SCREEN_PADDING, 10, 0.5);

    timespec deltaStart, deltaStop; 

    timespec_get(&deltaStart, TIME_UTC);

    while(Game.running)
    {   
        Input(); 

        Update();

        if(Draw() != 0)
        {
            QuitGame();

            return 1;
        }

        //mesure and set time
        timespec_get(&deltaStop, TIME_UTC);
        Game.deltaTime = deltaTime(deltaStart, deltaStop);
        Game.duration = timespecDiff(deltaStop, Game.start);
        timespec_get(&deltaStart, TIME_UTC);

        Processing();

        updateTimer(&Timer_frec10);

        Game.deltaDuration += Game.deltaTime;
        Game.fps = 1 / Game.deltaTime;
    }
    
    QuitGame();

    return 0;
}

int QuitGame(void){

    //clearQueue(&Processes);
    
    free(Data1.points);
    free(Data2.points);

    SDL_DestroyRenderer(Game.renderer);
    SDL_DestroyWindow(Game.window);    
    TTF_CloseFont(Game.fontRoboto);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

int Processing(){

    Process *process = NULL;
    int processPlace = 0;


    while(pollProcess(&process, &processPlace) == 0)
    {        
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
                        deQueue(&Processes ,processPlace);
                    }
                    else if(process->transition.endPoint < process->transition.startPoint && *process->transition.location <= process->transition.endPoint)
                    {
                        *process->transition.location = process->transition.endPoint;
                        deQueue(&Processes ,processPlace);
                    }
                }
                else if(process->transition.transitionType == smooth)
                {
                    destroyProcess(processPlace);
                }

            break;
        }
    };

    tidyQueue(&Processes);

    return 0;
}