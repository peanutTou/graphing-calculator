#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <iomanip>
#include <string>
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
    bool isVariable();
    bool isConstant();
    bool isMutipleVariable();
    double getConstant();
    double evaluate(double var);            //for sin, cos, etc.
    double evaluate(vector<double> var);    //for max, min, etc

    bool isNumberType();

    int argsNeedToEva();
    void setArgs(int args);
private:
    string _var;
    int _type;
    int _args;              //how many arguments need to call this function
    tokenType _typeEnum;
};


bool isThisAFunction(string isFunc);







#endif