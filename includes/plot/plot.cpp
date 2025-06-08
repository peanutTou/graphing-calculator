#include "plot.h"
#include <cmath>

plot::plot():_info(nullptr), _trans()
{}

plot::plot(graphInfo *info):_info(info), _trans(info)
{}

//do shunting yard and transformation
vector<sf::Vector2f> plot::cal_points(string equation)
{
    vector<sf::Vector2f> outPoints;
    ShuntingYard shuntingEquation(equation);

    RPN myRPN(shuntingEquation.postfix());

    if(_info->_displayCoor == 1)
    {
        //this is for cartesian coordiante
        float deltaX = (_info->_right - _info->_left) * 1.0 / MAX_PLOTS;
        float beginX = _info->_left;

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
    }
    else if(_info->_displayCoor == 2){
        //this is for polar coordiante
        float deltaX = (2 * M_PI) * 1.0 / MAX_PLOTS;
        float beginX = 0;

        for(int i = 0; i < MAX_PLOTS; i++)
        {
            sf::Vector2f originPosition(beginX, myRPN(beginX));

            //ignore nan output
            if(!std::isnan(originPosition.y)){
                //translate points from polar to carresian, ignore when the point on x is too large
                //reminader: r = originPosition.y, theta = beginX
                float toX = originPosition.y * cos(beginX);
                float toY = originPosition.y * sin(beginX);
                sf::Vector2f SFMLPosition = _trans.transform(sf::Vector2f(toX, toY));
                if(SFMLPosition.x <= PLAYGROUND_WIDTH){
                    outPoints.push_back(SFMLPosition);
                }
            }
            beginX += deltaX;
        }
    }
    else{
        cout << "unknown coordiante\n";
    }

    //find the point for the origin
    _info->_origin = _trans.transform(sf::Vector2f(0,0));
    return outPoints;

}
