#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include <string>
#include "token.h"
using namespace std;

class LeftParen : public Token
{
public:
    LeftParen();
    int typeOf() const;
    tokenType type();
    ostream& print(ostream &outs = cout) const;
    
private:
    int _type;
    tokenType _typeEnum;
    string _ch;
};






#endif
