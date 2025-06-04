#include "graphInfo.h"
#include <fstream>
#include <ostream>


graphInfo::graphInfo():hasChanged(true), _points(), equationHistory(), currentEquation(""), _origin(ORIGIN_REFEREN_X, ORIGIN_REFEREN_Y), _font(), buttonBounds()
{
    _top = INTERVAL_TOP;
    _bottom = INTERVAL_BOTTEM;
    _left = INTERVAL_LEFT;
    _right = INTERVAL_RIGHT;
    radius = 0;
    currentInputing = "";
    isCurrentInputValid = false;
    //loading fonts
    if(!_font.loadFromFile("ARIAL.TTF")){
        cout << "errer appears when loading fonts!!!\n";
    }
    readFromHistory();
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

void graphInfo::pushMyInput(){
    if(currentInputing == ""){
        return;
    }
    pushEquation(currentInputing);
    currentInputing = "";
}



void graphInfo::pushBounds(boundInfo newBound)
{
    buttonBounds.push_back(newBound);
}

int graphInfo::boundedCommand(float posx, float posy)
{
    for(int i = 0; i < buttonBounds.size(); i++){
        if(buttonBounds.at(i).isBounded(posx, posy)){
            return buttonBounds.at(i)._command;
        }
    }

    return -1;
}

ostream& operator <<(ostream& outs, const graphInfo &print){
    outs << "top: " << print._top << "  bottom: " << print._bottom << endl;
    outs << "left: " << print._left << "  right: " << print._right << endl;
    outs << "current equation: " << print.currentEquation << endl;
    outs << "origin: " << print._origin.x << " " << print._origin.y;
    return outs;
}


void graphInfo::writeInputToHistory()
{
    ofstream outFile(HISTORY_FILE_NAME);

    if (!outFile.is_open()) {
        cout << " error happens when writing in file!" << endl;
        return;
    }
    for(int i = 0; i < equationHistory.size(); i++){
        outFile << equationHistory.at(i) << "\n";
    }
    
    outFile.close();
}


void graphInfo::readFromHistory()
{
    string filePath = HISTORY_FILE_NAME;
    ifstream outFile(filePath);

    if (!outFile.is_open()) {
        cout << " error happens when reading in file!" << endl;
        return;
    }

    string lineEquation;

    while(std::getline(outFile, lineEquation)){
        pushEquation(lineEquation);
    }
    
    outFile.close();
}