
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdbool.h>

#define FRAME_CAP 60.0
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 780

#define FONT_SIZE 22

#define SCREEN_PADDING 30
#define LINE_HEIGHT 20

typedef struct{
    double deltaTime;
    double deltaDuration;
    float fps;
    time_t starTime;
    time_t timeDuration;
}gameTime;

typedef struct{
    double popGrowth;    
    double popState;
    int popSize;
    bool running;
}gameInfo;

typedef struct
{
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Color textColor;
    TTF_Font *textFont;
}renderInfo;

double DeltaTime(struct timespec s, struct timespec e);

int Input(gameTime *gameTime, gameInfo *gameInfo);
int Update(gameTime *gameTime, gameInfo *gameInfo);
int Draw(gameTime *gameTime, gameInfo *gameInfo, renderInfo *gameRend);


