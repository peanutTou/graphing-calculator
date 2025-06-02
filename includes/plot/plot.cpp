#include "plot.h"

plot::plot():_info(nullptr)
{}

plot::plot(graphInfo *info):_info(nullptr)
{

}

//do shunting yard and transformation
vector<sf::Vector2f> plot::get_points(string equation)
{
    vector<sf::Vector2f> outPoints;

    return outPoints;
}


// void plot::Plot(int x, int y, sf::RenderWindow& window)
// {
//     Plot(sf::Vector2f(x, y), window);
// }

// void plot::Plot(sf::Vector2f generCoor, sf::RenderWindow& window)
// {

//     sf::CircleShape point(PLOT_SIZE);
//     point.setFillColor(sf::Color::Red);

//     generCoor.x -= PLOT_SIZE;
//     generCoor.y -= PLOT_SIZE;
//     point.setPosition(generCoor);

//     window.draw(point);
// }