#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../constants.h"
#include "../graphInfo/graphInfo.h"
#include "../rpn_shuntingYard/rpn/rpn.h"
#include "../rpn_shuntingYard/shunting_yard/shunting_yard.h"
#include "../coor_transform/coor_transform.h"
using namespace std;

class plot{
public:
    plot();
    plot(graphInfo *info);

    vector<sf::Vector2f> cal_points(string equation);   //calculate points
    

private:
    graphInfo *_info;
    coor_transform _trans;
};







#endif