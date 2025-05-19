#include "number.h"


Number::Number():_type(1), _typeEnum(NUMBER)
{}

Number::Number(double num):_type(1), Token(), _typeEnum(NUMBER){
    _var = num;
}

Number::Number(string num):Token(), _type(1), _typeEnum(NUMBER){
    _var = stoi(num);
}

ostream& Number::print(ostream &outs) const{
    outs << _var;
    return outs;
}

//it's value
double Number::info(){
    return _var;
}

//it is a number
int Number::typeOf() const{
    return _type;
}

void Number::set(double num){
    _var = num;
}

tokenType Number::type(){
    return _typeEnum;
}