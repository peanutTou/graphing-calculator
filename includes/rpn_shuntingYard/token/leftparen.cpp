#include "leftparen.h"




LeftParen::LeftParen():Token(2), _type(2), _typeEnum(LEFTPARENT), _ch("(")
{}

int LeftParen::typeOf() const
{
    return _type;
}
tokenType LeftParen::type()
{
    return _typeEnum;
}
ostream& LeftParen::print(ostream &outs) const
{
    outs << _ch;
    return outs;
}