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
                splitedQue.push(new Integer(readChar));
                readChar = *str_walker;
                chType = 2;
            }
        }
        else if(isdigit(*str_walker)){
            if(chType == 0 || chType == 1){
                readChar += *str_walker;
                chType = 1;
            }
            else{
                splitedQue.push(new Function(readChar));
                readChar = *str_walker;
                chType = 1;
            }
        }
        else{
            if(chType == 1){
                splitedQue.push(new Integer(readChar));
            }
            else if(chType == 2){
                splitedQue.push(new Function(readChar));
            }

            chType = 0;

            if(*str_walker == '('){
                splitedQue.push(new LeftParen());
            }
            else if(*str_walker == ')'){
                splitedQue.push(new RightParen());
            }
            else{
                readChar = *str_walker;
                splitedQue.push(new Operator(readChar));
            }
            readChar = "";
        }
    }

    if(chType == 1){
        splitedQue.push(new Integer(readChar));
    }
    else if(chType == 2){
        splitedQue.push(new Function(readChar));
    }

    return splitedQue;
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

    // read each token from infix
    while(!infix.empty()){
        infixTop = infix.pop();
        if((infixTop->typeOf() == 1) || (infixTop->typeOf() == 3)){
            //numbers
            post_fix.push(infixTop);
        }
        else if(infixTop->typeOf() == 2){
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
                Operator* infixTopOper = static_cast<Operator*>(infixTop);
                Operator* topOper;
                bool isInifxPushed = false;
                while(!op_stack.empty() && op_stack.top()->type() != LEFTPARENT){
                    topOper = static_cast<Operator*>(op_stack.top());
                    
                    if(infixTopOper->operatorOrder() > topOper->operatorOrder()){
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