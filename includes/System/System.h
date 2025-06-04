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
#include "../graph/graph.h"
using namespace std;


class System{
public:
    System();
    System(graphInfo *info);

    void update(sf::RenderWindow& window);
    void drawGraph(sf::RenderWindow& window);
    void drawBackground(sf::RenderWindow& window);
    void drawDisplayUI(sf::RenderWindow& window);
    sf::RectangleShape drawFunctionDisplay(sf::RenderWindow& window, string f, sf::Vector2f size, sf::Vector2f position, int chSize);

    void mouseOnCliked(float posx, float posy);
private:
    graphInfo *_info;
    graph _g;
};






#endif