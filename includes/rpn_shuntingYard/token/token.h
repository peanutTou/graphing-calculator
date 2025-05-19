#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <iomanip>
#include <string>
#include "tokenType.h"
using namespace std;


class Token{
    public:
        Token();
        Token(int type);
        virtual int typeOf() const;
        virtual tokenType type();
        virtual ostream& print(ostream &outs = cout) const;
        friend ostream& operator <<(ostream& outs, const Token& print);
        friend ostream& operator <<(ostream& outs, const Token* print);
    private:
        int _type;           //1 - number, 2 - operator, 3 - function
};




#endif