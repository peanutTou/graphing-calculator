#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

static const float MAX_PLOTS = 300;             //how many plots can exist
static const float PLOT_SIZE = 1;               //each plot size

//inital intervals
static const float INTERVAL_LEFT = -30;
static const float INTERVAL_RIGHT = 30;
static const float INTERVAL_TOP = -30;
static const float INTERVAL_BOTTEM = 30;

//SFMLs
static const float SCREEN_WIDTH = 1100;
static const float SCREEN_HEIGHT = 800;


static const float PLAYGROUND_WIDTH = 800;
static const float PLAYGROUND_HEIGHT = 800;

static const std::string TITLE_NAME = "function calculator";

static const float ORIGIN_REFEREN_X = PLAYGROUND_WIDTH / 2;
static const float ORIGIN_REFEREN_Y = PLAYGROUND_HEIGHT / 2;

#endif