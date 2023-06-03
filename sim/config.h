#pragma once

//engine config
#define FRAME_CAP 30

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 780
#define SCREEN_PADDING 30

#define FONT_SIZE 24
#define LINE_HEIGHT 20

#define GRAPH_SAMPLING 0.1 //amount of samples per second

#define CAP_UNLIMITED 2147483647


//game settings
#define YEAR_TIME 1 //duration of year in seconds
#define POP_GROWTH 0.05 //pop growth in percents per year
#define POP_START_SIZE 120
#define FEED_RATE 0.02 //amount of food required to sustain population per second
#define HUNGER_RATE 1 //amount of hunger dropped per second


#define INIT_HAPPINESS 90
#define INIT_HUNGER 90

#define FOOD_RATE 1

//resource settings
#define AMOUNT_OF_REASOURCE_TYPES 3

#define FOOD_START_CAP 250
#define FOOD_START_AMOUNT 100
#define WOOD_START_CAP 250
#define WOOD_START_AMOUNT 0
#define STONE_START_CAP 250
#define STONE_START_AMOUNT 0

//jobs settings
#define AMOUNT_OF_JOB_TYPES 3

//other relationships
#define STARVATION_SPAN 100 / HUNGER_RATE //amount of time where population will go from 100 to 0 hunger
#define FOOD_TO_HUNGER HUNGER_RATE / FEED_RATE //used to translate food amount int amount of hunger satisfied
