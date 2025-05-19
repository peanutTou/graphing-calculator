#include "rpn.h"
#include "assert.h"

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

double RPN::operator()(int var_val){
    bool debug = false;
    if(debug){
        cout << "entering Rpn::Operator();" << endl;
    }
    
    double value = evaluate(var_val);
    
    return value;
}

double RPN::evaluate(int var_val)
{
    //evaluate
    Queue<Token*> rpn_cal = input_q;


    Stack<double> rpn_stack;
    Token *poped_op;

    while(!rpn_cal.empty()){
         poped_op = rpn_cal.pop();
        if(poped_op->typeOf() == 1){
            //number
            rpn_stack.push(static_cast<Number*>(poped_op)->info());
        }
        else if(poped_op->typeOf() == 2){
            //operator
            double left, right, result;
            assert(rpn_stack.size() >= 2 && "number stack doesn't have enough elements but trying pop()");
            right = rpn_stack.pop();
            left = rpn_stack.pop();
            result = static_cast<Operator*>(poped_op)->evaluate(left, right);
            rpn_stack.push(result);
        }
        else if(poped_op->typeOf() == 3){
            //function
            rpn_stack.push(var_val);
        }
        else{
            cout << "\ntypeof: " << poped_op->typeOf() << endl;
            assert(false && "Rpn::Evaluate(), rpn_stack has a token was not either number or operators\n");
        }
    }

    assert(rpn_stack.size() == 1 && "there shoud have one value left in stack!");

    return rpn_stack.pop();

}