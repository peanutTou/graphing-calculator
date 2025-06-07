#include "shunting_yard.h"
#include <cctype>

ShuntingYard::ShuntingYard()
{

}
ShuntingYard::ShuntingYard(Queue<Token*> infix):input_que(infix)
{
} 


ShuntingYard::ShuntingYard(string infix){
    input_que = stringToQueue(infix);
}

void ShuntingYard::inputPostfix(string str){
    while(!input_que.empty()){
        input_que.pop();
    }
    input_que = stringToQueue(str);
}

//split infix by number, letter, Special characters
//read for each character,
//if number, push to Integer token
//if letter, push to function token
//if Special characters, think if it is a operator
Queue<Token*> ShuntingYard::stringToQueue(string str){
    char* str_walker;
    Queue<Token*> splitedQue;
    int chType = 0;             //1 - number, 2 - letter
    string readChar = "";

    for(int i = 0; i < str.size(); i++){
        str_walker = &str.at(i);
        if(*str_walker == ' '){
            continue;
        }
        if(isalpha(*str_walker)){
            if(chType == 0 || chType == 2){
                readChar += *str_walker;
                chType = 2;
            }
            else{
                pushInteger(splitedQue, readChar);
                readChar = *str_walker;
                chType = 2;
            }

            if(isThisAFunction(readChar)){
                pushFunction(splitedQue, readChar);
                chType = 0;
                readChar = "";
            }
        }
        else if(isdigit(*str_walker) || *str_walker == '.' ){
            if(chType == 0 || chType == 1){
                readChar += *str_walker;
                chType = 1;
            }
            else{
                pushFunction(splitedQue, readChar);
                readChar = *str_walker;
                chType = 1;
            }
        }
        else{
            if(chType == 1){
                pushInteger(splitedQue, readChar);
            }
            else if(chType == 2){
                pushFunction(splitedQue, readChar);
            }

            chType = 0;

            if(*str_walker == '('){
                autoMakeUpOper(splitedQue, "drop");
                splitedQue.push(new LeftParen());
            }
            else if(*str_walker == ')'){
                splitedQue.push(new RightParen());
            }
            else{
                readChar = *str_walker;
                bool isUnaryOper = false;
                if(readChar == "+" || readChar == "-")
                {
                    if(splitedQue.empty() || (!splitedQue.top()->isNumberType() && splitedQue.top()->type() != RIGHTPARENT)){
                        isUnaryOper = true;
                    }
                }

                splitedQue.push(new Operator(readChar, isUnaryOper));
            }
            readChar = "";
        }
    }

    if(chType == 1){
        pushInteger(splitedQue, readChar);
    }
    else if(chType == 2){
        pushFunction(splitedQue, readChar);
    }


    //finally, count how many left paren, make up for missing right paren
    int countl = 0, countr = 0;
    for(Queue<Token*>::Iterator it = splitedQue.begin(); it != splitedQue.end(); it++){
        if((*it)->type() == LEFTPARENT){
            countl++;
        }
        if((*it)->type() == RIGHTPARENT){
            countr++;
        }
    }

    for(int i = countr; i < countl; i++){
        splitedQue.push(new RightParen());
    }

    return splitedQue;
}


//if reading things like 2x, consider as 2*x
void ShuntingYard::autoMakeUpOper(Queue<Token*>& splitedQue, string readChar)
{
    if(!splitedQue.empty() && readChar != "pi"){
        if(splitedQue.top()->typeOf() == 1){
            splitedQue.push(new Operator("*"));
        }
        if(!splitedQue.empty() && splitedQue.top()->type() == RIGHTPARENT){
            splitedQue.push(new Operator("*"));
        }
        if(splitedQue.top()->typeOf() == 3){
            Function* func = static_cast<Function*>(splitedQue.top());
            if(func->isConstant() || func->isVariable()){
                splitedQue.push(new Operator("*"));
            }
        }
    }
}


//push when case is a function
void ShuntingYard::pushFunction(Queue<Token*>& splitedQue, string readChar)
{
    autoMakeUpOper(splitedQue, readChar);

    splitedQue.push(new Function(readChar));
}

//push when case is a number
void ShuntingYard::pushInteger(Queue<Token*>& splitedQue, string readChar)
{
    if(readChar == "."){
        readChar = "0";
    }
    if(!splitedQue.empty() && splitedQue.top()->type() == RIGHTPARENT){
        splitedQue.push(new Operator("*"));
    }
    splitedQue.push(new Number(readChar));
}

//push when case is an operator
void ShuntingYard::pushOperator(Queue<Token*>& splitedQue, string readChar)
{

}




Queue<Token*> ShuntingYard::postfix(){
    return postfix(input_que);
}


void ShuntingYard::infix(Queue<Token*> input){
    input_que = input;
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> infix){
    Queue<Token*> post_fix;          //result
    Stack<Token*> op_stack;         //stack for operator
    Token* infixTop;             //poped tokens for infix
    bool thisIsNotFunc = false;

    // read each token from infix
    while(!infix.empty()){
        thisIsNotFunc = false;
        infixTop = infix.pop();
        if((infixTop->typeOf() == 1)){
            //numbers
            post_fix.push(infixTop);
        }
        else if(infixTop->typeOf() == 3){
            //function but still numbers
            Function* inFunc = static_cast<Function*>(infixTop);
            if(inFunc->isConstant() || inFunc->isVariable()){
                post_fix.push(infixTop);
                thisIsNotFunc = true;
            }
        }

        if(infixTop->typeOf() == 2 || (infixTop->typeOf() == 3 && !thisIsNotFunc)){
            //operators
            if(infixTop->type() == LEFTPARENT){
                op_stack.push(infixTop);
            }
            else if(infixTop->type() == RIGHTPARENT){
                while(!op_stack.empty() && (op_stack.top())->type() != LEFTPARENT){
                    post_fix.push(op_stack.pop());
                }

                if(!op_stack.empty()){
                    op_stack.pop();
                }
            }
            else{
                int holdingOrder;  //order for holding operator
                if(infixTop->typeOf() == 3){
                    holdingOrder = 4;
                }
                else{
                    Operator* infixTopOper = static_cast<Operator*>(infixTop);
                    holdingOrder = infixTopOper->operatorOrder();
                }
                Token* topOper; //for topper operator
                int toperOrder;
                bool isInifxPushed = false;
                while(!op_stack.empty() && op_stack.top()->type() != LEFTPARENT){
                    topOper = op_stack.top();
                    if(topOper->typeOf() == 3){
                        toperOrder = 4;
                    }
                    else{
                        toperOrder = static_cast<Operator*>(topOper)->operatorOrder();
                    }
                    
                    if(holdingOrder > toperOrder){
                        op_stack.push(infixTop);
                        isInifxPushed = true;
                        break;
                    }
                    else{
                        post_fix.push(op_stack.pop());
                    }
                }
                if(!isInifxPushed){
                    op_stack.push(infixTop);
                }
            }
        }
    }
    //push tokens from op_stack to postFix
    while(!op_stack.empty()){
        infixTop = op_stack.pop();
        post_fix.push(infixTop);
    }

    return post_fix;
}