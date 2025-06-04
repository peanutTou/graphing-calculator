#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H


//show token types, and it's number is it's order for operator
enum tokenType{
    EMPTY = -1,     //empty, other, or some thing can't be understand
    DOUBLE,
    NUMBER, 
    PLUS = 1,
    MINUS = 1,
    MULTIPLE = 2,
    DIVISION = 2,
    LEFTPARENT,
    RIGHTPARENT,
    FUNCTION,
    POWER
};

#endif