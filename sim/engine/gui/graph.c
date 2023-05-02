#include "graph.h"

Graph MainGraph;
GraphData Data1;

void Init_Graph(Graph *graph, int size, int posX, int posY, float scaleX, float scaleY, float ofsetX, float ofsetY){

    graph->position.w = size;
    graph->position.h = size;
    graph->position.x = posX;
    graph->position.y = posY;
    graph->scaleX = size * scaleX / 100;
    graph->scaleY = size * scaleY / 100;
    graph->ofsetX = ofsetX;
    graph->ofsetY = ofsetY;

    return;
}

void addDataPoint(GraphData *data, float pointX, float pointY){

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

    int ofset = graph.position.w * 0.025;

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

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLines(rend, arr, data.size);

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
}