#include "graphInfo.h"

boundInfo::boundInfo():_bounds(0, 0, 0, 0), _command(-1)
{}

boundInfo::boundInfo(float left, float top, float width, float height, int command):
                                                            _bounds(left, top, width, height),
                                                             _command(command)
{}

boundInfo::boundInfo(sf::FloatRect bounds, int command):_bounds(bounds),_command(command)
{}

bool boundInfo::isBounded(float posX, float posY) const
{
    return _bounds.contains(posX, posY);
}



ostream& operator <<(ostream& outs, const boundInfo& boundin){
    outs << boundin._bounds.top << " " << boundin._bounds.left << " ";
    outs << boundin._bounds.height << " " << boundin._bounds.width << " ";
    outs << "command: " << boundin._command;
    return outs;
}