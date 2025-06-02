#include "plot.h"

plot::plot():_info(nullptr), _trans()
{}

plot::plot(graphInfo *info):_info(info), _trans(info)
{

}

//do shunting yard and transformation
vector<sf::Vector2f> plot::cal_points(string equation)
{
    vector<sf::Vector2f> outPoints;

    ShuntingYard shuntingEquation(equation);
    RPN myRPN(shuntingEquation.postfix());

    float deltaX = (INTERVAL_RIGHT - INTERVAL_LEFT) * 1.0 / MAX_PLOTS;
    float beginX = INTERVAL_LEFT;
    for(int i = 0; i < MAX_PLOTS; i++)
    {
        sf::Vector2f originPosition(beginX, myRPN(beginX));
        sf::Vector2f SFMLPosition = _trans.transform(originPosition);
        outPoints.push_back(SFMLPosition);
        beginX += deltaX;
        // cout << outPoints[0].x << " " << outPoints[0].y << endl;
    }
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


// string testEquation = "x * (x + 1) * (x + 2) + 10";
    // ShuntingYard shuntingEquation(testEquation);
    // RPN myRPN(shuntingEquation.postfix());

    // float deltaX = (INTERVAL_RIGHT - INTERVAL_LEFT) * 1.0 / MAX_PLOTS;
    // float beginX = INTERVAL_LEFT;
    // for(int i = 0; i < MAX_PLOTS; i++)
    // {
    //     beginX += deltaX;
    //     sf::Vector2f originPosition(beginX, myRPN(beginX));
    //     sf::Vector2f drawPosition = coorTransformation(originPosition);
    //     _ploter.Plot(drawPosition, window);
    // }