#ifndef COMMA_H
#define COMMA_H
#include <string>
#include "token.h"
using namespace std;

class comma : public Token
{
public:
    comma();

    int typeOf() const; //return by integers
    tokenType type();   //return by enums
    ostream& print(ostream &outs = cout) const;
    
private:
    int _type;
    tokenType _typeEnum;
    string _ch;
};


#endif
