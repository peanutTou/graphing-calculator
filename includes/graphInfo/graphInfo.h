#ifndef GRAPHINFO_H
#define GRAPHINFO_H
#include "../constants.h"
#include "../rpn_shuntingYard/shunting_yard/shunting_yard.h"
#include "../rpn_shuntingYard/rpn/rpn.h"
#include "../vector/vector_class.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>



//boundInfo will collect the bound region and send out command when it is been clicked
struct boundInfo{
    sf::FloatRect _bounds;
    int _command;

    boundInfo();
    boundInfo(float left, float top, float width, float height, int command);
    boundInfo(sf::FloatRect bounds, int command);

    bool isBounded(float posX, float posY) const;

    friend ostream& operator <<(ostream& outs, const boundInfo& boundin);
};





struct graphInfo
{
    //every time when the structure has some changes, turn this on
    bool hasChanged;
    sf::Font _font;

    //region of the interval (bounce)
    float _top;
    float _bottom;
    float _left;
    float _right;

    sf::Vector2f _origin;

    //used memebers
    Vector<sf::Vector2f> _points;   //to save plot calculated points
    Vector<boundInfo> buttonBounds;
    int selectedHistoryIndex;       //start at 300, increase 10 for each ++
    int _displayCoor;                //1 -> Cartesian, 2 -> polar

    //input managers
    Vector<string> equationHistory;
    string currentEquation;
    string currentInputing;
    bool isCurrentInputValid;
    bool isInputingFunction;


    //functions
    graphInfo();
    void resetInterval(float top, float bottom, float left, float right);
    void setOrigin(sf::Vector2f origin);
    void offChanged();                      //after finish a update, think every changes has been fixed

    //input related
    void pushEquation(string equation);     //push an equation on the top
    void deleteEquation(int index);         //delte an equation with the index
    void pushMyInput();                     //push current input to history
    void writeInputToHistory();
    int getHistoryTureIndex(int i);

    //buttons related
    void pushBounds(boundInfo newBound);        //container for boundInfo
    int boundedCommand(float posx, float posy); //return a command if clicked a button

    void moveInterval(int dir); //1 top, 2 left, 3 bottom, 4 right
    void zoomIn();
    void zoomOut();
    void reset();

    void coorChanges();
    friend ostream& operator <<(ostream& outs, const graphInfo &print);


private:
    void readFromHistory();                 //read history files, only be called when initlized
};


#endif