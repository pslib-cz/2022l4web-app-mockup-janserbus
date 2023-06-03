#include "graph.h"

graph PopulationGraph;
data PopulationData;

void Graph_init(graph *Graph, SDL_Point origin, int size, float scaleX, float scaleY, float ofsetX, float ofsetY, char *lableX, char *lableY){
    
    Graph->origin.x = origin.x;
    Graph->origin.y = origin.y + size;
    Graph->size = size;
    strcpy(Graph->lableX, lableX);
    strcpy(Graph->lableY, lableY);
    Graph->ofsetXinit = ofsetX;
    Graph->ofsetYinit = ofsetY;

    //calculate scale based on graph size (to make graphed data same on all graph sizes)
    Graph->scaleXinit = size * scaleX / 100;
    Graph->scaleYinit = size * scaleY / 100;
    Graph->scaleX = size * scaleX / 100;
    Graph->scaleY = size * scaleY / 100;
    Graph->ofsetX = ofsetX;
    Graph->ofsetY = ofsetY;
}

void Graph_update(graph *Graph, SDL_Point origin, int size, float scaleX, float scaleY, float ofsetX, float ofsetY){
    Graph->origin.x = origin.x;
    Graph->origin.y = origin.y + size;
    Graph->size = size;
    Graph->scaleX = scaleX;
    Graph->scaleY = scaleY;
    Graph->ofsetX = ofsetX;
    Graph->ofsetY = ofsetY;
}

void Graph_updateScale(graph *Graph, float scaleX, float scaleY){

    Graph->scaleY = Graph->size * scaleY / 100;
    Graph->scaleX = Graph->size * scaleX / 100;
}
void Graph_updateOfset(graph *Graph, float ofsetX, float ofsetY){

    Graph->ofsetX = ofsetX;
    Graph->ofsetY = ofsetY;
}
void Graph_updateOrigin(graph *Graph, SDL_Point origin){

    Graph->origin.x = origin.x;
    Graph->origin.y = origin.y + Graph->size;
}
void Graph_updateSize(graph *Graph, int size){

    Graph->size = size;
    Graph->scaleY = size * Graph->scaleY / 100;
    Graph->scaleX = size * Graph->scaleX / 100;
}

void Graph_render(SDL_Renderer *rend, graph Graph, SDL_Color color){

    int ofset = Graph.size * 0.025;

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLine(rend, Graph.origin.x - ofset, Graph.origin.y, Graph.origin.x + Graph.size + ofset, Graph.origin.y);
    SDL_RenderDrawLine(rend, Graph.origin.x, Graph.origin.y + ofset, Graph.origin.x, Graph.origin.y - Graph.size - ofset);

    //graph segments drawing
    for(int i = 0; i < 10; i++)
    {
        //TODO draw segments to scale
        
        int segmentXPos, segmentYPos, segmentOfset, segmentSpacing;

        segmentSpacing = Graph.size / 10;

        segmentYPos = Graph.origin.y - segmentSpacing * (i + 1);
        segmentXPos = Graph.origin.x + segmentSpacing * (i + 1);

        segmentOfset = ofset / 2;

        //draws horizontal segments
        SDL_RenderDrawLine(rend, segmentXPos, Graph.origin.y - segmentOfset, segmentXPos, Graph.origin.y + segmentOfset);

        //TODO render text for each segment

        //draws vertical segments
        SDL_RenderDrawLine(rend, Graph.origin.x - segmentOfset, segmentYPos, Graph.origin.x + segmentOfset, segmentYPos);
    }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);    
}

void Data_addPoint(data *data, double pointX, double pointY){

    if(data->points == NULL)
    {
        data->points = malloc(sizeof(SDL_FPoint));   
        data->size = 0;
    }
    else
    {
        data->points = realloc(data->points, (data->size + 1) * sizeof(SDL_FPoint));
    }

    data->points[data->size].x = pointX;
    data->points[data->size].y = pointY;

    data->size++;
}

void RenderGraphData(SDL_Renderer *rend, graph Graph, data Data, SDL_Color color){

    SDL_Point arr[Data.size];

    //TODO eliminate overlaping points to make line smooth based on scale and ofset
    //TODO exclude points outside of graph range

    //transform data to be show on a graph (aply offset and scale)
    for(int i = 0; i < Data.size; i++)
    {
        arr[i].x = (round(Data.points[i].x) - Graph.ofsetX) * Graph.scaleX + Graph.origin.x;
        arr[i].y = (-round(Data.points[i].y) - Graph.ofsetY) * Graph.scaleY + Graph.origin.y;
    }

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLines(rend, arr, Data.size);

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
}
