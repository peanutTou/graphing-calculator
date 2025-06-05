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
    isInputingFunction = false;
    selectedHistoryIndex = 0;
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


/* each bounded area will own a command
    -1 : no command
    100: open function input box
    200: go last page
    201: go next page
    300: use history equation as current
    301: delete this history equation
    302: let this history being current input   
    for history setting, each index will have a different value, for second index, it will be 310,311,312 
    401: move interval up
    402: move interval left
    403: move interval down
    404: move interval right
    500: zoom in
    501: zoom out
    999: reset
*/
void graphInfo::pushBounds(boundInfo newBound)
{
    buttonBounds.push_back(newBound);
}

/* each bounded area will own a command
    -1 : no command
    100: open function input box
    200: go last page
    201: go next page
    300: use history equation as current
    301: delete this history equation
    302: let this history being current input   
    for history setting, each index will have a different value, for second index, it will be 310,311,312 
    401: move interval up
    402: move interval left
    403: move interval down
    404: move interval right
    500: zoom in
    501: zoom out
    999: reset
*/
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


//reading and writing history file
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



int graphInfo::getHistoryTureIndex(int i)
{
    return equationHistory.size() - i - 1;
}


void graphInfo::moveInterval(int dir){
    float intervalSize = _right - _left;
    float moveRate = intervalSize * 0.3;
    if(dir == 1){
        _top -= moveRate;
        _bottom -= moveRate;
        _origin.y -= moveRate;
    }
    else if(dir == 2){
        _left -= moveRate;
        _right -= moveRate;
        _origin.x -= moveRate;
    }
    else if(dir == 3){
        _top += moveRate;
        _bottom += moveRate;
        _origin.y += moveRate;
    }
    else if(dir == 4){
        _left += moveRate;
        _right += moveRate;
        _origin.x += moveRate;
    }
    else{
        cout << "graphInfo::moveInterval::::\"invalid direction\"\n";
    }
}


void graphInfo::zoomIn()
{
    _top *= 0.8;
    _bottom *= 0.8;
    _left *= 0.8;
    _right *= 0.8;
}
void graphInfo::zoomOut()
{
    _top *= 1.2;
    _bottom *= 1.2;
    _left *= 1.2;
    _right *= 1.2;
}