#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include <string>
#include "token.h"
using namespace std;

class RightParen : public Token
{
public:
    RightParen();
    int typeOf() const;
    tokenType type();
    ostream& print(ostream &outs = cout) const;
    
private:
    int _type;
    tokenType _typeEnum;
    string _ch;
};





#endif