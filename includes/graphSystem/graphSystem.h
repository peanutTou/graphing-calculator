#ifndef GRAPHSYSTEM_H
#define GRAPHSYSTEM_H
#include <iostream>
#include <iomanip>
#include <string>
#include "../plot/plot.h"
#include "../rpn_shuntingYard/shunting_yard/shunting_yard.h"
#include "../rpn_shuntingYard/rpn/rpn.h"
#include "../constants.h"
using namespace std;


class graphSystem{
public:
    graphSystem();

    void update(sf::RenderWindow& window);
    void drawPlot(sf::RenderWindow& window);
    void drawBackground(sf::RenderWindow& window);

    sf::Vector2f coorTransformation(float x, float y);
    sf::Vector2f coorTransformation(sf::Vector2f origin);

private:
    plot _ploter;
};






#endif