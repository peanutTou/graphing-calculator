#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iomanip>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "../graphInfo/graphInfo.h"
#include "../rpn_shuntingYard/shunting_yard/shunting_yard.h"
#include "../rpn_shuntingYard/rpn/rpn.h"
#include "../plot/plot.h"
using namespace std;


class graph{
public:
    graph();
    graph(graphInfo *info);

    void update(sf::RenderWindow& window);
    void graph_function(sf::RenderWindow& window);  //calcluate points and draw
    void getPoints();                               //get a vector of points by ploter
    void drawPointes(sf::RenderWindow& window);     //draw the points
private:
    graphInfo *_info;
    plot _ploter;
};






#endif