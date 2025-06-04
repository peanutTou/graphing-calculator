#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H
#include <iostream>
#include <iomanip>
#include <string>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

#include "../token/token.h"
#include "../token/operator.h"
#include "../token/integer.h"
#include "../token/function.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
using namespace std;


class ShuntingYard{
public:
    ShuntingYard();
    ShuntingYard(Queue<Token*> infix);                //input a infinx equation and turns to postfix
    ShuntingYard(string infix);                            //input a string equation and turns to postfix

    Queue<Token*> postfix(Queue<Token*> infix);        //translate infix to postfix
    Queue<Token*> postfix();
    void inputPostfix(string str);
    void infix(Queue<Token*> input);    //input infix
    
private:
    Queue<Token*> input_que;

    Queue<Token*> stringToQueue(string str);  //flag false when some operator can't be understand
};






#endif