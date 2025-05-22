#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "../plot/plot.h"
#include "../rpn_shuntingYard/shunting_yard/shunting_yard.h"
#include "../rpn_shuntingYard/rpn/rpn.h"
#include "../constants.h"
#include "../graphInfo/graphInfo.h"
using namespace std;


class System{
public:
    System();
    System(graphInfo *info);

    void update(sf::RenderWindow& window);
    void drawPlot(sf::RenderWindow& window);
    void drawBackground(sf::RenderWindow& window);

    sf::Vector2f coorTransformation(float x, float y);
    sf::Vector2f coorTransformation(sf::Vector2f origin);

private:
    graphInfo *_info;
    plot _ploter;
};






#endif