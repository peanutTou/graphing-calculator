#include "token.h"



Token::Token():_type(0)
{}

Token::Token(int t):_type(t)
{}


ostream& Token::print(ostream &outs) const
{
    return outs;
}

bool Token::isNumberType(){
    return false;
}


int Token::typeOf() const{
    bool debug = false;
    if(debug){
        cout << "Token::TypeOf()" << endl;
    }
    
    return _type;
}

tokenType Token::type(){
    return EMPTY;
}




ostream& operator <<(ostream& outs, const Token& print){
    print.print(outs);

    return outs;
}

ostream& operator <<(ostream& outs, const Token* print){
    print->print(outs);

    return outs;
}
