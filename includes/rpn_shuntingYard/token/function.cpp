#include "function.h"


Function::Function()
{
    _var = "X";
    _type = 3;
    _typeEnum = FUNCTION;
}
Function::Function(string var):Token()
{
    _var = var;
    _type = 3;
    _typeEnum = FUNCTION;
}
Function::Function(char var):Token(), _var(var, 1)
{
    _type = 3;
    _typeEnum = FUNCTION;
}


int Function::typeOf() const
{
    return _type;
}
ostream& Function::print(ostream &outs) const
{
    outs << _var;
    return outs;
}

tokenType Function::type(){
    return _typeEnum;
}