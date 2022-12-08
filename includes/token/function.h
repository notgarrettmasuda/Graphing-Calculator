#ifndef FUNCTION_H
#define FUNCTION_H

#include "../token/token.h"

class Function : public Token
{
    public:
        //CTOR
        Function(string func) : _func(func) {}

        string get_func()
        {
            return _func;
        }

        TOKEN_TYPES get_type() override
        {
            return FUNCTION;
        }
        void Print(ostream &outs) const override
        {
            outs << _func;
        }

    private:
        string _func;
};

#endif