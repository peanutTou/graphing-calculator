#include "comma.h"



comma::comma():Token(2), _type(2), _typeEnum(COMMA), _ch(",")
{}

int comma::typeOf() const
{
    return _type;
}
tokenType comma::type()
{
    return _typeEnum;
}
ostream& comma::print(ostream &outs) const
{
    outs << _ch;
    return outs;
}