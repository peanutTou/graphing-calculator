#include "integer.h"

Integer::Integer()
{}

Integer::Integer(int number):Number(number)
{}

Integer::Integer(string num):Number(num)
{
    
}
    
double Integer::info()
{
    return Number::info();
}

void Integer::set(int number)
{
    Number::set(number);
}

int numberType(){
    return 1;
}