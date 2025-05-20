#include "vector2d.h"
#include <cmath>
#include "assert.h"

vector2d::vector2d():x(0),y(0)
{}

vector2d::vector2d(float vx, float vy):x(vx), y(vy)
{}


float vector2d::magnitude(){
    float inside = x*x + y*y;
    return sqrt(inside);
}


vector2d operator +(const vector2d& left, const vector2d &right)
{
    return vector2d(left.x + right.x, left.y + right.y);
}
vector2d operator -(const vector2d& left, const vector2d &right)
{
    return vector2d(left.x - right.x, left.y - right.y);
}
vector2d operator *(const vector2d& left, float right)
{
    return vector2d(left.x*right, left.y*right);
}

vector2d vector2d::operator -()
{
    return vector2d(-x, -y);
}
vector2d& vector2d::operator +=(const vector2d &v)
{
    x += v.x;
    y += v.y;
    return *this;
}
vector2d& vector2d::operator -=(const vector2d& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}
vector2d& vector2d::operator *=(float f)
{
    x *= f;
    y *= f;
    return *this;
}

float vector2d::operator[](int index){
    if(index == 0){
        return x;
    }
    else if(index == 1){
        return y;
    }else{
        assert(false && "for vector2d[] operator, only 0 for x, 1 for y are valued");
        return 0;
    }
}