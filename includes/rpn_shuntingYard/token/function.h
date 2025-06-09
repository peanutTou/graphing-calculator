#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <iomanip>
#include <string>
#include "../../vector/vector_class.h"
#include "token.h"
using namespace std;

class Function: public Token{
public:
    Function();
    Function(string var);
    Function(string var, int args);
    Function(char var);

    int typeOf() const; //what is the type, in integer
    ostream& print(ostream &outs = cout) const;
    tokenType type();   //what is the type, in enum

    bool isVariable();          //not a function, and not a constant
    bool isConstant();          //pi
    bool isNumberType();        //a combine for isVariable and isConstant
    bool isMutipleVariable();   //true when max, min

    
    //for evaluate function, if a function used a wrong version, return nan("");
    double getConstant();                   //for constant version evaluate
    double evaluate(double var);            //for sin, cos, etc.
    double evaluate(Vector<double> var);    //for max, min, etc


    int argsNeedToEva();    //arguments need to evaluate
    void setArgs(int args);
private:
    string _var;
    int _type;
    int _args;              //how many arguments need to call this function
    tokenType _typeEnum;
};


bool isThisAFunction(string isFunc);    //collects all type of functions







#endif