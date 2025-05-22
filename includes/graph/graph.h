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
using namespace std;


class graph{
public:
    graph();
    graph(graphInfo *info);

    void update();

private:
    graphInfo *_info;
};






#endif