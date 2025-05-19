#ifndef INTEGER_H
#define INTEGER_H
#include <iostream>
#include <iomanip>
#include <string>
#include "number.h"
using namespace std;


class Integer: public Number{
public:
    Integer();
    Integer(int number);
    Integer(string num);
    
    double info();
    void set(int number);
};






#endif