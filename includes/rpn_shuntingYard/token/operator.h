#ifndef OPERATOR_H
#define OPERATOR_H
#include <iostream>
#include <iomanip>
#include <string>
#include "token.h"
using namespace std;


class Operator: public Token
{
public:
    Operator();
    Operator(string op, tokenType type);
    Operator(string op);

    int typeOf() const;
    virtual double evaluate(double left, double right);
    ostream& print(ostream &outs = cout) const;
    string operType();
    tokenType type();

    //compare operators, compare which operator have a hight order
    friend bool operator ==(const Operator &left, const Operator &right);
    friend bool operator >=(const Operator &left, const Operator &right);
    friend bool operator <=(const Operator &left, const Operator &right);
    friend bool operator >(const Operator &left, const Operator &right);
    friend bool operator <(const Operator &left, const Operator &right);
    friend bool operator !=(const Operator &left, const Operator &right);

    int operatorOrder();
private:
    string _oper;             //operator type
    tokenType _operEnum;
    int _type;              //2

    void readStringType();  //determind the enumerator type by string
};






#endif