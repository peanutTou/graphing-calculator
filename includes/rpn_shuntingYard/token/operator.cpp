#include "operator.h"
#include "assert.h"
#include <cmath>
Operator::Operator():_type(2),_isUnary(false)
{}

Operator::Operator(string oper, tokenType type, bool isunary):Token(),_type(2), _oper(oper), _operEnum(type),_isUnary(isunary)
{}

Operator::Operator(string oper, bool isunary):Token(), _type(2), _oper(oper),_isUnary(isunary)
{
    readStringType();
}


int Operator::typeOf() const
{
    bool debug = false;
    if(debug){
        cout << "Operator::typeOf()" << endl;
    }
    
    return _type;
}

double Operator::evaluate(double left, double right)
{
    if(_oper == "+"){
       return left + right;
    }
    else if(_oper == "-"){
        return left - right;
    }
    else if(_oper == "*"){
        return left * right;
    }
    else if(_oper == "/"){
        return left / right;
    }
    else if(_oper == "^"){
        return pow(left, right);
    }

    cout << "\noper: " << _oper << endl;
    cout << "not a evaluable operator\n" << endl;
    return 0;
}

string Operator::operType(){
    return _oper;
}

ostream& Operator::print(ostream& outs) const{
    outs << _oper;
    return outs;
}

tokenType Operator::type(){
    return _operEnum;
}

int Operator::operatorOrder(){
    if(_isUnary){
        return 3;
    }
    if(_oper == "+" || _oper == "-"){
        return 1;
    }
    else if(_oper == "*" || _oper == "/"){
        return 2;
    }
    else if(_oper == "^"){
        return 5;
    }
    return -1;
}

void Operator::readStringType(){

    if(_oper == "+"){
        _operEnum = PLUS;
    }
    else if(_oper == "-"){
        _operEnum = MINUS;
    }
    else if(_oper == "*"){
        _operEnum = MULTIPLE;
    }
    else if(_oper == "/"){
        _operEnum = DIVISION;
    }
    else if(_oper == "("){
        _operEnum = LEFTPARENT;
    }
    else if(_oper == ")"){
        _operEnum = RIGHTPARENT;
    }
    else if(_oper == "^"){
        _operEnum = POWER;
    }
    else{
        _operEnum = EMPTY;
    }
}

bool operator ==(const Operator &left, const Operator &right)
{
    return left._operEnum == right._operEnum;
}
bool operator >=(const Operator &left, const Operator &right)
{
    return left._operEnum >= right._operEnum;
}
bool operator <=(const Operator &left, const Operator &right)
{
    return left._operEnum <= right._operEnum;
}
bool operator >(const Operator &left, const Operator &right)
{
    return left._operEnum > right._operEnum;
}
bool operator <(const Operator &left, const Operator &right)
{
    return left._operEnum < right._operEnum;
}
bool operator !=(const Operator &left, const Operator &right)
{
    return left._operEnum != right._operEnum;
}