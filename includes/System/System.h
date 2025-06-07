#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "../plot/plot.h"
#include "../rpn_shuntingYard/shunting_yard/shunting_yard.h"
#include "../rpn_shuntingYard/rpn/rpn.h"
#include "../constants.h"
#include "../graphInfo/graphInfo.h"
#include "../graph/graph.h"
using namespace std;


class System{
public:
    System();
    System(graphInfo *info);

    void update(sf::RenderWindow& window);              //call each draw function and display

    void drawBackground(sf::RenderWindow& window);      //draw xy-asix, UI display areas
    void drawGraph(sf::RenderWindow& window);           //plot the function
    void drawDisplayUI(sf::RenderWindow& window);       //draw UI
    void drawHistoryEquations(sf::RenderWindow& window);//display 10 latest history equations


    void mouseOnCliked(float posx, float posy);          //player clicked the mouse, find what button been clicked
    void callCommand(int com);                           //do job with command
private:
    graphInfo *_info;
    graph _g;

    //a collected function to draw a white with text
    sf::RectangleShape drawFunctionDisplay(sf::RenderWindow& window,    //object to draw
                                            string f,                   //string want to display
                                            sf::Vector2f size,          //the size of the box want to create
                                            sf::Vector2f position,      //where to draw
                                            int chSize,                 //string character size
                                            bool drawBoarder = false);  //does this box want to have a boarder

};

//get a float, convery to string, keep two decimals
 string floatToSting(float f);




#endif