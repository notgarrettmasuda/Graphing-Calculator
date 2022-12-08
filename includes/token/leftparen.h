#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include "../token/token.h"

class LeftParen : public Token
{
    public:
        TOKEN_TYPES get_type()
        {
            return LPAREN;
        }
        
        void Print(ostream &outs) const override
        {
            outs << "(";
        }
};

#endif