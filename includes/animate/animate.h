#ifndef ANIMATE_H
#define ANIMATE_H
#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../graphSystem/graphSystem.h"
#include "../constants.h"
#include <string>
using namespace std;

class animate{
public:
    animate();
    void startAnimate();
    ~animate();
private:
    sf::RenderWindow _windows;
    graphSystem _sys;
};







#endif