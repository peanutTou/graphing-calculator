#include "System.h"

System::System():_ploter(),_info(nullptr)
{}

System::System(graphInfo *info): _info(info), _ploter()
{}


void System::update(sf::RenderWindow& window)
{
    window.clear();
    drawBackground(window);
    drawPlot(window);
    window.display();
}


void System::drawPlot(sf::RenderWindow& window)
{
    string testEquation = "x * (x + 1) * (x + 2) + 10";
    ShuntingYard shuntingEquation(testEquation);
    RPN myRPN(shuntingEquation.postfix());

    float deltaX = (INTERVAL_RIGHT - INTERVAL_LEFT) * 1.0 / MAX_PLOTS;
    float beginX = INTERVAL_LEFT;
    for(int i = 0; i < MAX_PLOTS; i++)
    {
        beginX += deltaX;
        sf::Vector2f originPosition(beginX, myRPN(beginX));
        sf::Vector2f drawPosition = coorTransformation(originPosition);
        _ploter.Plot(drawPosition, window);
    }
}


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

sf::Vector2f System::coorTransformation(float x, float y){

    float sclarX = SCREEN_WIDTH / (INTERVAL_RIGHT - INTERVAL_LEFT);
    float sclarY = SCREEN_HEIGHT / (INTERVAL_BOTTEM - INTERVAL_TOP);

    float cx = x * sclarX + ORIGIN_REFEREN_X;
    float cy = ORIGIN_REFEREN_Y - y * sclarY;

    return sf::Vector2f(cx, cy);
}

sf::Vector2f System::coorTransformation(sf::Vector2f origin){
    return coorTransformation(origin.x, origin.y);
}