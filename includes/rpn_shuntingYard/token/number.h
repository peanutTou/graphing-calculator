#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <iomanip>
#include <string>
#include "token.h"
using namespace std;


class Number: public Token{
    public:
        Number();
        Number(double num);
        Number(string num);

        tokenType type();
        ostream& print(ostream &outs = cout) const;
        virtual double info();
        int typeOf() const;
        void set(double num);
        bool isNumberType();

    private:
        int _type;              //1
        double _var;
        tokenType _typeEnum;
};







#endif