#include "operator.h"
#include "assert.h"
Operator::Operator():_type(2)
{}

Operator::Operator(string oper, tokenType type):Token(),_type(2), _oper(oper), _operEnum(type)
{}

Operator::Operator(string oper):Token(), _type(2), _oper(oper)
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

    cout << "\noper: " << _oper << endl;
    assert(false && "not a evaluable operator\n");
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
    if(_oper == "+" || _oper == "-"){
        return 1;
    }
    else if(_oper == "*" || _oper == "/"){
        return 2;
    }

    cout << "\noperator: " << _oper << endl;
    assert(false && "don't have an operator order\n");
    return 0;
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