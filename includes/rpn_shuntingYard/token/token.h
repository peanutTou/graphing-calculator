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


        virtual int typeOf() const; //number type
        virtual tokenType type();   //enum type
        virtual ostream& print(ostream &outs = cout) const;
        virtual bool isNumberType();//default false

        //friend print functions
        friend ostream& operator <<(ostream& outs, const Token& print);
        friend ostream& operator <<(ostream& outs, const Token* print);

    private:
        int _type;           //1 - number, 2 - operator, 3 - function
};




#endif