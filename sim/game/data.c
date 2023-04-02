#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "data.h"

//initializing game data structures
GameData Game;
Graph MainGraph;
GraphData Data1;
GraphData Data2;
Population Population1;
Population Population2;

int Init_GameData(){

    Game.running = true;
    Game.fps = 0;

    Game.deltaTime = 0;
    Game.deltaDuration = 0;
    Game.duration.tv_sec = 0;
    Game.duration.tv_nsec = 0;
    timespec_get(&(Game.start), TIME_UTC);

    Game.window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!Game.window){
        printf("Error initializing GameData: %s\n", SDL_GetError());
        return 1;    
    }

    Game.renderer = SDL_CreateRenderer(Game.window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!Game.renderer){
        printf("Error initializing GameData: %s\n", SDL_GetError());
        SDL_DestroyWindow(Game.window);
        return 1;
    }

    Game.fontRoboto = TTF_OpenFont("fonts/Roboto.ttf", FONT_SIZE);
    if(!Game.fontRoboto){
        printf("Error initializing GameData: %s\n", TTF_GetError());
        SDL_DestroyRenderer(Game.renderer);
        SDL_DestroyWindow(Game.window);
        return 2;
    }

    Game.colorWite.r = 255;    
    Game.colorWite.g = 255;    
    Game.colorWite.b = 255;    
    Game.colorWite.a = 255;

    Game.colorRed.r = 255;    
    Game.colorRed.g = 0;    
    Game.colorRed.b = 0;    
    Game.colorRed.a = 255;

    return 0;
}

void Init_Population(Population *population, char name[], int size, double growth){
    
    strcpy(population->name, name);
    population->size = size;
    population->state = size;
    population->growth = growth;
}

void Init_Graph(Graph *graph, int size, int posX, int posY, float scaleX, float scaleY){

    graph->position.w = size;
    graph->position.h = size;
    graph->position.x = posX;
    graph->position.y = posY;
    graph->scaleX = scaleX;
    graph->scaleY = scaleY;

    return;
}

void addDataPoint(GraphData *data, double pointX, double pointY){

    if(data->points == NULL)
    {
        data->points = malloc(sizeof(SDL_Point));        
        data->size = 0;
    }
    else
    {
        data->points = realloc(data->points, (data->size + 1) * sizeof(SDL_Point));
    }

    data->points[data->size].x = round(pointX);
    data->points[data->size].y = round(pointY);

    data->size++;
}

void RenderGraph(SDL_Renderer *rend, Graph graph, SDL_Color color){

    int ofset = 10;

    SDL_Point origin;

    origin.x = graph.position.x;
    origin.y = graph.position.y + graph.position.h;

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLine(rend, origin.x - ofset, origin.y, origin.x + graph.position.w + ofset, origin.y);
    SDL_RenderDrawLine(rend, origin.x, origin.y + ofset, origin.x, origin.y - graph.position.h - ofset);

    //TODO draw graph segments

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);    
}

void RenderGraphData(SDL_Renderer *rend, Graph graph, GraphData data, SDL_Color color){

    SDL_Point arr[data.size];

    for(int i = 0; i < data.size; i++)
    {
        arr[i] = data.points[i];
    }

    //apply ofset and scale to data    

    for(int i = 0; i < data.size; i++)
    {
        arr[i].x = arr[i].x * graph.scaleX + graph.position.x;
        arr[i].y = -arr[i].y * graph.scaleY + graph.position.y + graph.position.h;
    }

    // SDL_Point arr[2];
    // arr[0].x = graph.position.x;
    // arr[0].y = graph.position.y + graph.position.h;
    // arr[1].x = graph.position.x + 500;
    // arr[1].y = graph.position.y + graph.position.h - 500;


    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLines(rend, arr, data.size);

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
}