#include "graphInfo.h"


graphInfo::graphInfo():hasChanged(true), _points(), equationHistory(), currentEquation(""), _origin(400, 400)
{
    _top = INTERVAL_TOP;
    _bottom = INTERVAL_BOTTEM;
    _left = INTERVAL_LEFT;
    _right = INTERVAL_RIGHT;
    radius = 0;
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
//push an equation on the top
void graphInfo::pushEquation(string equation)
{
    currentEquation = equation;
    equationHistory.push_back(equation);
    hasChanged = true;
}

//delte an equation with the index
void graphInfo::deleteEquation(int index)
{
    if(equationHistory.size() > index){
        //if is deleteing top equation
        if(equationHistory.size() - 1 == index){
            equationHistory.pop_back();
            if(equationHistory.size() > 0){
                currentEquation = equationHistory[equationHistory.size() - 1];
            }
            else{
                currentEquation = "";
            }
        }
        else{
            equationHistory.erase(equationHistory.begin() + index);
        }
    }
    hasChanged = true;
} 



ostream& operator <<(ostream& outs, const graphInfo &print){
    outs << "top: " << print._top << "  bottom: " << print._bottom << endl;
    outs << "left: " << print._left << "  right: " << print._right << endl;
    outs << "current equation: " << print.currentEquation << endl;
    outs << "origin: " << print._origin.x << " " << print._origin.y;
    return outs;
}