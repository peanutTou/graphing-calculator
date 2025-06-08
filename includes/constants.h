#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

static const std::string HISTORY_FILE_NAME = "input_history.txt";

static const float MAX_PLOTS = 500;             //how many plots can exist
static const float PLOT_SIZE = 1;               //each plot size
static const float MAX_JUMP_VALUE = 0.6;        //if y changes so qulickly in a short time, cut the line

static const bool DRAW_GRAPH_WITH_LINE = false; //does want to graph the line

//SFMLs
static const std::string TITLE_NAME = "function calculator";

static const float SCREEN_WIDTH = 1100;
static const float SCREEN_HEIGHT = 800;


static const float PLAYGROUND_WIDTH = 800;
static const float PLAYGROUND_HEIGHT = 800;


//inital intervals
static const float INTERVAL_LEFT = -5;
static const float INTERVAL_RIGHT = 5;
static const float INTERVAL_TOP = 5;
static const float INTERVAL_BOTTEM = -5;

static const float ORIGIN_REFEREN_X = PLAYGROUND_WIDTH / 2;
static const float ORIGIN_REFEREN_Y = PLAYGROUND_HEIGHT / 2;

#endif