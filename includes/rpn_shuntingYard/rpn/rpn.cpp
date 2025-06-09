#include "rpn.h"
#include "assert.h"
#include "../../vector/vector_class.h"

RPN::RPN():input_q()
{}

RPN::RPN(Queue<Token*> postfix):input_q(postfix)
{}



RPN::RPN(const RPN& r):input_q(r.input_q)
{}

RPN& RPN::operator =(const RPN& RHS)
{
    if(this == &RHS){
        return *this;
    }
    input_q = RHS.input_q;

    return *this;
}

void RPN::set_input(Queue<Token*> postfix){
    input_q = postfix;
}

double RPN::operator()()
{
    bool debug = false;
    if(debug){
        cout << "entering Rpn::Operator();" << endl;
    }
    
    double value = evaluate();
    return value;
}

double RPN::operator()(double var_val){
    bool debug = false;
    if(debug){
        cout << "entering Rpn::Operator();" << endl;
    }
    
    double value = evaluate(var_val);
    
    return value;
}

double RPN::evaluate(double var_val)
{
    //evaluate
    Queue<Token*> rpn_cal = input_q;
    if(rpn_cal.size() == 0){
        return std::nan("");
    }

    Stack<double> rpn_stack;
    Token *poped_op;

    while(!rpn_cal.empty()){
         poped_op = rpn_cal.pop();
        if(poped_op->typeOf() == 1){
            //number
            rpn_stack.push(static_cast<Number*>(poped_op)->info());
        }
        else if(poped_op->typeOf() == 2){
            if(poped_op->type() == LEFTPARENT || poped_op->type() == RIGHTPARENT || poped_op->type() == COMMA){
                return std::nan("");
            }
            if(rpn_stack.size() == 0){
                return std::nan("");
            }
            //operator
            double left, right, result;
            Operator* ppop = static_cast<Operator*>(poped_op);

            // Unary operators
            if(ppop->isUnary()){
                right = rpn_stack.pop();
                result = ppop->evaluate(0, right);
                rpn_stack.push(result);
                continue;
            }


            //assert(rpn_stack.size() >= 2 && "number stack doesn't have enough elements but trying pop()");
            if(rpn_stack.size() < 2){
                return std::nan("");
            }

            right = rpn_stack.pop();
            left = rpn_stack.pop();
            result = ppop->evaluate(left, right);
            rpn_stack.push(result);
        }
        else if(poped_op->typeOf() == 3){
            //function
            Function* inFun = static_cast<Function*>(poped_op);
            if(inFun->isVariable()){
                //if the function is a variable
                rpn_stack.push(var_val);
            }
            else if(inFun->isConstant()){
                //if the function is a constant
                rpn_stack.push(inFun->getConstant());
            }
            else{
                //function is a function (like sin, cos...)
                if(rpn_stack.size() == 0){
                    return std::nan("");
                }
                
                if(inFun->argsNeedToEva() == 1){
                    //function with one argument need
                    rpn_stack.push(inFun->evaluate(rpn_stack.pop()));
                }
                else{
                    //function with many arguments need
                    Vector<double> arguments;
                    int argNeed = inFun->argsNeedToEva();
                    if(rpn_stack.size() < argNeed){
                        return std::nan("");
                    }
                    for(int i = 0; i < argNeed; i++){
                        arguments.push_back(rpn_stack.pop());
                    }
                    rpn_stack.push(inFun->evaluate(arguments));
                }
            }
            
        }
        else{
            cout << "\ntypeof: " << poped_op->typeOf() << endl;
            // assert(false && "Rpn::Evaluate(), rpn_stack has a token was not either number or operators\n");
            return std::nan("");
        }
    }


    if(rpn_stack.size() != 1){
        return std::nan("");
    }


    return rpn_stack.pop();

}