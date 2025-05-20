#include "plot.h"

plot::plot()
{

}


void plot::Plot(int x, int y, sf::RenderWindow& window)
{
    Plot(sf::Vector2f(x, y), window);
}

void plot::Plot(sf::Vector2f generCoor, sf::RenderWindow& window)
{

    sf::CircleShape point(PLOT_SIZE);
    point.setFillColor(sf::Color::Red);

    generCoor.x -= PLOT_SIZE;
    generCoor.y -= PLOT_SIZE;
    point.setPosition(generCoor);

    window.draw(point);
}