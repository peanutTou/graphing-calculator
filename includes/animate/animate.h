#ifndef ANIMATE_H
#define ANIMATE_H
#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "../System/System.h"
#include "../constants.h"
#include "../graphInfo/graphInfo.h"
using namespace std;

class animate{
public:
    animate();
    void startAnimate();
    ~animate();
private:
    sf::RenderWindow _windows;
    graphInfo *_info;
    System _sys;
};







#endif