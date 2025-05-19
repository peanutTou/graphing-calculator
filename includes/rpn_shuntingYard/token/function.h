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
    Function(char var);

    int typeOf() const;
    ostream& print(ostream &outs = cout) const;
    tokenType type();
private:
    string _var;
    int _type;
    tokenType _typeEnum;
};








#endif