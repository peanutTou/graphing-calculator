#ifndef GRAPHINFO_H
#define GRAPHINFO_H
#include "../constants.h"
#include "../rpn_shuntingYard/shunting_yard/shunting_yard.h"
#include "../rpn_shuntingYard/rpn/rpn.h"


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
struct graphInfo
{
    //every this structure has some changes, turn this on
    bool hasChanged;

    //region of the interval (bounce)
    float _top;
    float _bottom;
    float _left;
    float _right;

    sf::Vector2f _origin;
    float radius;   //for rotation
    //used memebers
    vector<sf::Vector2f> _points;   //to save plot calculated points


    //input equations
    vector<string> equationHistory;
    string currentEquation;

    //functions
    graphInfo();
    void resetInterval(float top, float bottom, float left, float right);
    void setOrigin(sf::Vector2f origin);
    void offChanged();
    void pushEquation(string equation); //push an equation on the top
    void deleteEquation(int index);  //delte an equation with the index

    friend ostream& operator <<(ostream& outs, const graphInfo &print);
    //TODO:: shifting interval functions, for top, left
};





#endif