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

        //ignore nan output
        if(!std::isnan(originPosition.y)){
            sf::Vector2f SFMLPosition = _trans.transform(originPosition);
            outPoints.push_back(SFMLPosition);
        }
        beginX += deltaX;
    }
    return outPoints;
}
