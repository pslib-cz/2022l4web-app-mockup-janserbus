#pragma once

#include <SDL2/SDL.h>

typedef struct data{
    SDL_FPoint *points;
    int size;
}data;

typedef struct graph{
    SDL_Point origin;
    int size;
    float ofsetXinit;
    float ofsetYinit;
    float scaleXinit;
    float scaleYinit;
    float scaleX;
    float scaleY;    
    float ofsetX;
    float ofsetY;
    char lableX[20];
    char lableY[20];
}graph;


void Graph_init(graph *Graph, SDL_Point origin, int size, float scaleX, float scaleY, float ofsetX, float ofsetY, char *lableX, char *lableY);

void Graph_update(graph *Graph, SDL_Point origin, int size, float scaleX, float scaleY, float ofsetX, float ofsetY);
void Graph_updateScale(graph *Graph, float scaleX, float scaleY);
void Graph_updateOfset(graph *Graph, float ofsetX, float ofsetY);
void Graph_updateOrigin(graph *Graph, SDL_Point origin);
void Graph_updateSize(graph *Graph, int size);

void Graph_render(SDL_Renderer *rend, graph Graph, SDL_Color color);

void Data_addPoint(data *data, double pointX, double pointY);
void RenderGraphData(SDL_Renderer *rend, graph graph, data data, SDL_Color color);


extern graph PopulationGraph;
extern data PopulationData;