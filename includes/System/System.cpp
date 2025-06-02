#include "System.h"

System::System():_g(),_info(nullptr)
{}

System::System(graphInfo *info): _info(info), _g(info)
{}


void System::update(sf::RenderWindow& window)
{
    window.clear();
    drawBackground(window);
    drawGraph(window);
    window.display();
}


void System::drawGraph(sf::RenderWindow& window)
{
    _g.update(window);
}

//draw xy axis
void System::drawBackground(sf::RenderWindow& window)
{
    sf::RectangleShape x_axis(sf::Vector2f(SCREEN_WIDTH, 1));
    x_axis.setFillColor(sf::Color::White);
    x_axis.setPosition(sf::Vector2f(0, ORIGIN_REFEREN_Y));

    window.draw(x_axis);

    sf::RectangleShape y_axis(sf::Vector2f(1, SCREEN_HEIGHT));
    y_axis.setFillColor(sf::Color::White);
    y_axis.setPosition(sf::Vector2f(ORIGIN_REFEREN_X, 0));

    window.draw(y_axis);
}