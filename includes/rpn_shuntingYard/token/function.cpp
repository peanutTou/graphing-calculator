#include "function.h"
#include <cmath>
#include <vector>


Function::Function()
{
    _var = "X";
    _type = 3;
    _typeEnum = FUNCTION;
    _args = 1;
}

Function::Function(string var):Token(), _args(1)
{
    _var = var;
    _type = 3;
    _typeEnum = FUNCTION;
}

Function::Function(char var):Token(), _var(var, 1), _args(1)
{
    _type = 3;
    _typeEnum = FUNCTION;
}

Function::Function(string var, int args):Token(), _args(args)
{
    _var = var;
    _type = 3;
    _typeEnum = FUNCTION;
    
}

int Function::argsNeedToEva()
{
    return _args;
}
void Function::setArgs(int args)
{
    _args = args;
}

bool Function::isVariable()
{
    bool isAfunc = !isThisAFunction(_var);
    return isAfunc;
}

bool Function::isConstant(){
    if(_var == "pi"){
        return true;
    }
    return false;
}

bool Function::isMutipleVariable(){
    if(_var == "max" || _var == "min"){
        return true;
    }
    return false;
}
double Function::getConstant(){
    if(_var == "pi"){
        return M_PI;
    }
    return 0;
}

bool Function::isNumberType(){
    if(isConstant() || isVariable()){
        return true;
    }
    return false;
}

double Function::evaluate(double var)
{
    if(_var == "sin"){
        return sin(var);
    }
    else if(_var == "cos"){
        return cos(var);
    }
    else if(_var == "tan"){
        return tan(var);
    }
    else if(_var == "csc"){
        return 1/sin(var);
    }
    else if(_var == "sec"){
        return 1/cos(var);
    }
    else if(_var == "cot"){
        return 1/tan(var); 
    }
    else if(_var == "arcsin"){
        return asin(var);
    }
    else if(_var == "arccos"){
        return acos(var);
    }
    else if(_var == "arctan"){
        return atan(var);
    }
    else if(_var == "arccsc"){
        return asin(1/var);
    }
    else if(_var == "arcsec"){
        return acos(1/var);
    }
    else if(_var == "arccot"){
        return atan(1/var);
    }
    else if(_var == "exp"){
        return pow(M_E, var);
    }
    else if(_var == "sqrt"){
        return sqrt(var);
    }
    else if(_var == "log"){
        return log(var);
    }
    else if(_var == "ln"){
        //use change base formula
        float n = log(var);
        float d = log(M_E);
        return n/d;
    }

    return std::nan("");
}

double Function::evaluate(vector<double> var)
{
    if(var.size() == 0){
        return std::nan("");
    }

    if(_var == "max")
    {
        int max = var.at(0);
        for(int i = 1; i < var.size(); i++){
            if(var.at(i) > max){
                max = var.at(i);
            }
        }
        return max;
    }
    else if(_var == "min")
    {
        int min = var.at(0);
        for(int i = 1; i < var.size(); i++){
            if(var.at(i) > min){
                min = var.at(i);
            }
        }
        return min;
    }



    return std::nan("");
}



int Function::typeOf() const
{
    return _type;
}
ostream& Function::print(ostream &outs) const
{
    outs << _var;
    return outs;
}

tokenType Function::type(){
    return _typeEnum;
}


bool isThisAFunction(string isFunc){
    vector<string> names = {"sin", "cos", "tan", "csc", "sec", "cot", "arcsin", "arccos", "arctan",
                             "arccsc", "arcsec", "arccot", "exp", "sqrt", "pi", "log", "ln", "max", "min"};

    bool isContain = false;
    for(int i = 0; i < names.size(); i++){
        if(names.at(i) == isFunc){
            isContain = true;
            break;
        }
    }

    return isContain;
}