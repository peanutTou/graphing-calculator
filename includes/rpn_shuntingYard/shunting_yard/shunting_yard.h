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
#include "../token/comma.h"
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

    void pushFunction(Queue<Token*>& splitedQue, string readChar);
    void pushInteger(Queue<Token*>& splitedQue, string readChar);
    void autoMakeUpOper(Queue<Token*>& splitedQue, string readChar);  //if reading things like 2x, consider as 2*x
};






#endif