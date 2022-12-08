#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include "../token/token.h"

class RightParen : public Token
{
    public:
        TOKEN_TYPES get_type()
        {
            return RPAREN;
        }

        void Print(ostream &outs) const override
        {
            outs << ")";
        }
};

#endif