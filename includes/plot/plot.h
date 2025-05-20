#ifndef PLOT_H
#define PLOT_H
#include <iostream>
#include <iomanip>
#include <string>
#include <SFML/Graphics.hpp>
#include "../constants.h"
#include <SFML/Window.hpp>
using namespace std;

class plot{
public:
    plot();

    void Plot(int x, int y, sf::RenderWindow& window);
    void Plot(sf::Vector2f point, sf::RenderWindow& window);

private:
};







#endif