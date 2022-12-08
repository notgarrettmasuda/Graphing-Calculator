#ifndef OPERATOR_H
#define OPERATOR_H

#include "../token/token.h"

class Operator : public Token
{
    public:
        //CTOR
        Operator(string op) : _op(op) {}

        string get_op()
        {
            return _op;
        }

        TOKEN_TYPES get_type() override
        {
            return OPERATOR;    
        }

        void Print(ostream &outs) const override
        {
            outs << _op;
        }
        
    private:
        string _op;
};

#endif