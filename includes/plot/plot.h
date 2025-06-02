#ifndef PLOT_H
#define PLOT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../constants.h"
#include "../graphInfo/graphInfo.h"
using namespace std;

class plot{
public:
    plot();
    plot(graphInfo *info);

    vector<sf::Vector2f> get_points(string equation);
    

private:
    graphInfo *_info;
};







#endif