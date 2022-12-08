#ifndef INTEGER_H
#define INTEGER_H

#include "../token/token.h"

class Integer : public Token
{
    public:
        //CTOR
        Integer(double var) : _var(var) {} 

        double get_var()
        {
            return _var;
        }

        TOKEN_TYPES get_type() override 
        {
            return INTEGER;
        }

        void Print(ostream &outs) const override
        {
            outs << _var;
        }

    private:
        double _var;
};

#endif