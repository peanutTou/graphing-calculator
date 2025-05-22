#include "graphInfo.h"


graphInfo::graphInfo():_plotter(),hasChanged(true), _points(), inputEquation(), currentEquation("")
{
    _top = INTERVAL_TOP;
    _bottom = INTERVAL_BOTTEM;
    _left = INTERVAL_LEFT;
    _right = INTERVAL_RIGHT;
}


void graphInfo::resetInterval(float top, float bottom, float left, float right)
{
    _top = top;
    _bottom = bottom;
    _left = left;
    _right = right;

    hasChanged = true;
}

void graphInfo::setOrigin(sf::Vector2f origin){
    _origin = origin;
    hasChanged = true;
}

void graphInfo::offChanged(){
    hasChanged = false;
}
