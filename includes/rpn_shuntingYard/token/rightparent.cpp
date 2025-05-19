#include "rightparen.h"



RightParen::RightParen():Token(2), _type(2), _typeEnum(RIGHTPARENT), _ch(")")
{}

int RightParen::typeOf() const
{
    return _type;
}
tokenType RightParen::type()
{
    return _typeEnum;
}
ostream& RightParen::print(ostream &outs) const
{
    outs << _ch;
    return outs;
}