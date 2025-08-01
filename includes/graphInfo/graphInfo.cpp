#include "graphInfo.h"
#include <fstream>
#include <ostream>


graphInfo::graphInfo():hasChanged(true), _points(), equationHistory(), _font(), buttonBounds(), selectedHistoryIndex(0)
{
    reset();
    _displayCoor = 1;
    currentInputing = "";
    currentEquation = "";
    isCurrentInputValid = false;
    isInputingFunction = false;
    _inputIndex = 0;

    //loading fonts
    if(!_font.loadFromFile("ARIAL.TTF")){
        cout << "errer appears when loading fonts!!!\n";
    }
    else{
        readFromHistory();
    }
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
        equationHistory.erase(index);
        hasChanged = true;
    }
} 

void graphInfo::pushMyInput(){
    if(currentInputing == ""){
        return;
    }
    pushEquation(currentInputing);
    currentInputing = "";
    _inputIndex = 0;
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
    601: change coordinate
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
    601: change coordinate
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

    bool debug = false;
    if(debug){
        cout << "which input in to history file successly" << endl;
    }
}


void graphInfo::readFromHistory()
{
    string filePath = HISTORY_FILE_NAME;
    ifstream inFile(filePath);

    if (!inFile.is_open()) {
        pushEquation("1/x");
        ofstream outFile(HISTORY_FILE_NAME);
        outFile.close();
        return;
    }

    string lineEquation;

    while(std::getline(inFile, lineEquation)){
        pushEquation(lineEquation);
    }
    
    inFile.close();


    bool debug = false;
    if(debug){
        cout << "load history file successly" << endl;
    }
    
}


int graphInfo::getHistoryTureIndex(int i)
{
    return equationHistory.size() - i - 1;
}

//add the character to the current insert location
void graphInfo::addInput(char ch)
{
    if(ch == 127){
        if(currentInputing == "") return;
        int eraseIndex = _inputIndex - 1;
        _inputIndex--;
        if(eraseIndex < 0){
            eraseIndex = 0;
            _inputIndex = 0;
        }
        
        currentInputing.erase(currentInputing.begin() + eraseIndex);
        if(_inputIndex > currentInputing.size()){
            _inputIndex = currentInputing.size();
        }
    }
    else{
        currentInputing.insert(currentInputing.begin() + _inputIndex, ch);
        _inputIndex++;
    }
}

//move the insert location around respect to -1 and 1 (left, right)
void graphInfo::inputIndexMove(int dir){
    if(dir > 0)
    {
        _inputIndex++;
        if(_inputIndex > currentInputing.size()){
            _inputIndex = currentInputing.size();
        }
    }
    else if(dir < 0)
    {
        _inputIndex--;
        if(_inputIndex < 0){
            _inputIndex = 0;
        }
    }
}

//get the size of the interval, and move for a move by a certain rate
void graphInfo::moveInterval(int dir){
    hasChanged = true;
    float intervalSize = _right - _left;
    float moveRate = intervalSize * 0.03;
    if(dir == 1){   //top
        _top -= moveRate;
        _bottom -= moveRate;
    }
    else if(dir == 2){  //left
        _left -= moveRate;
        _right -= moveRate;
    }
    else if(dir == 3){  //bottom
        _top += moveRate;
        _bottom += moveRate;
    }
    else if(dir == 4){  //right
        _left += moveRate;
        _right += moveRate;
    }
    else{
        cout << "graphInfo::moveInterval::::\"invalid direction\"\n";
    }
}


//find the center point on the screen, zoom in respect to this point
void graphInfo::zoomIn()
{
    float sclar = 0.8;
    bool debug = false;
    if(debug){
        cout << "zoomIn  with sclar: " << sclar << endl;
    }

    hasChanged = true;
    float centerX = (_right + _left) / 2;
    float centerY = (_top + _bottom) / 2;

    _top = (_top - centerY) * sclar + centerY;
    _left = (_left - centerX) * sclar + centerX;
    _bottom = (_bottom - centerY) * sclar + centerY;
    _right = (_right - centerX) * sclar + centerX;
}
void graphInfo::zoomOut()
{
    float sclar = 1.25;
    bool debug = false;
    if(debug){
        cout << "zoomOut with sclar: " << sclar << endl;
    }

    hasChanged = true;
    float centerX = (_right + _left) / 2;
    float centerY = (_top + _bottom) / 2;

    _top = (_top - centerY) * sclar + centerY;
    _left = (_left - centerX) * sclar + centerX;
    _bottom = (_bottom - centerY) * sclar + centerY;
    _right = (_right - centerX) * sclar + centerX;
}


//change every interval value to default
void graphInfo::reset(){
    hasChanged = true;
    _top = INTERVAL_TOP;
    _bottom = INTERVAL_BOTTEM;
    _left = INTERVAL_LEFT;
    _right = INTERVAL_RIGHT;
    _origin = sf::Vector2f(ORIGIN_REFEREN_X, ORIGIN_REFEREN_Y);
}



void graphInfo::coorChanges(){
    bool debug = false;
    if(debug){
        cout << "coorChanges!!!" << endl;
    }
    
    if(_displayCoor == 1)
    {
        _displayCoor = 2;
    }
    else{
        _displayCoor = 1;
    }
}