#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdbool.h>

#include "time.h"

#define FRAME_CAP 60.0

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 780
#define SCREEN_PADDING 30

#define FONT_SIZE 24
#define LINE_HEIGHT 20

typedef struct{
    SDL_Point *points;
    int size;
}GraphData;

typedef struct{
    SDL_Rect position;
    float scaleX;
    float scaleY;    
}Graph;

typedef struct{
    char name[10];
    double growth;
    double state;
    long size;
}Population;

typedef struct{
    bool running;
    float fps;
    double deltaTime;
    double deltaDuration;
    timespec duration;
    timespec start;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *fontRoboto;
    SDL_Color colorWite;
    SDL_Color colorRed;
}GameData;

//prototypes
int Input();
int Update();
int Draw();

int Init_GameData();
void Init_Population(Population *population, char name[], int size, double growth);
void Init_Graph(Graph *graph, int size, int posX, int posY, float scaleX, float scaleY);

void addDataPoint(GraphData *data, double pointX, double pointY);
void RenderGraph(SDL_Renderer *rend, Graph graph, SDL_Color color);
void RenderGraphData(SDL_Renderer *rend, Graph graph, GraphData data, SDL_Color color);

//get initialize game structures to use globaly
extern GameData Game;
extern Graph MainGraph;
extern GraphData Data1;
extern GraphData Data2;
extern Population Population1;
extern Population Population2;