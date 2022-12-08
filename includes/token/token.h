#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

using namespace std;

#include "../token/constants.h"

class Token
{
  public:
    virtual TOKEN_TYPES get_type();
    virtual void Print(ostream &outs) const;
    friend ostream& operator <<(ostream& outs, const Token* token);
    friend ostream &operator<<(ostream &outs, const Token &token);
};


TOKEN_TYPES Token::get_type()
{
  return TOKEN;
}

void Token::Print(ostream &outs) const
{
  outs << "TOKEN Print: DON't ^%#$# call me again!" << endl;
}

ostream& operator <<(ostream& outs, const Token* token)
{
  token->Print(outs);
  return outs;
}

ostream &operator <<(ostream &outs, const Token &token)
{
  token.Print(outs);
  return outs;
}

#endif