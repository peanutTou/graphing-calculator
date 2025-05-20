#ifndef RPN_H
#define RPN_H
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


class RPN{
public:

    RPN();
    RPN(Queue<Token*> postfix);    //input a postfix equation
    RPN(const RPN& r);

    RPN& operator =(const RPN& RHS);
    double operator()();
    double operator()(double var_val);
    double evaluate(double var_val = 0);
    void set_input(Queue<Token*> postfix);

private:
    Queue<Token*> input_q;
};






#endif