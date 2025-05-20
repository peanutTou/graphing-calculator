#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


struct vector2d
{
    float x;
    float y;

    vector2d();
    vector2d(float vx, float vy);
    float magnitude();

    friend vector2d operator +(const vector2d& left, const vector2d &right);    //vector add
    friend vector2d operator -(const vector2d& left, const vector2d &right);    //vector minus
    friend vector2d operator *(const vector2d& left, float right);              //scalar mutiple
    vector2d operator -();
    vector2d& operator +=(const vector2d &v);
    vector2d& operator -=(const vector2d& RHS);
    vector2d& operator *=(float f);
    float operator[](int index);    //0-x, 1-y, other - error
};










#endif