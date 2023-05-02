#pragma once

#include <SDL2/SDL.h>

typedef struct{
    SDL_Point *points;
    int size;
}GraphData;

typedef struct{
    SDL_Rect position;
    float scaleX;
    float scaleY;    
    float ofsetX;
    float ofsetY;
}Graph;


void Init_Graph(Graph *graph, int size, int posX, int posY, float scaleX, float scaleY, float ofsetX, float ofsetY);
void addDataPoint(GraphData *data, float pointX, float pointY);
void RenderGraph(SDL_Renderer *rend, Graph graph, SDL_Color color);
void RenderGraphData(SDL_Renderer *rend, Graph graph, GraphData data, SDL_Color color);


extern Graph MainGraph;
extern GraphData Data1;