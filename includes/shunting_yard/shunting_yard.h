#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <cassert>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

using namespace std;

class ShuntingYard
{
public:
  // CTOR
  ShuntingYard(){}
  ShuntingYard(const Queue<Token*>& input_q)
  {
    queue = input_q;
  }

  // save input_q to member variable queue
  void infix(const Queue<Token*>& input_q)
  {
    queue = input_q;
  }

  int precedence(Token* var)
  {
    if (var->get_type() == OPERATOR)
    {
      Operator* temp_o = static_cast<Operator*>(var);
      if (temp_o->get_op() == "+" || temp_o->get_op() == "-")
      {
        return 1;
      }
      else if (temp_o->get_op() == "*" || temp_o->get_op() == "/")
      {
        return 2;
      }
      if (temp_o->get_op() == "^")
      {
        return 3;
      }
    }
    else if (var->get_type() == FUNCTION)
    {
      return 4;
    }
    return -1;
  }
  
  // generate postfix queue from infix queue
  Queue<Token*> postfix()
  {
    return shunting_yard();
  }
  Queue<Token*> postfix(const Queue<Token*>& input_q)
  {
    queue = input_q;
    return shunting_yard();
  }
  // called by postfix() 
  Queue<Token*> shunting_yard()
  {
    Queue<Token*> res_queue;
    Stack<Token*> op_stack;
    while (queue.size() > 0)
    {
      Token* token = queue.front();
      if (token->get_type() == INTEGER)
      {
        res_queue.push(token);
      }
      else if (token->get_type() == FUNCTION)
      {
        Function* temp_f = static_cast<Function*>(token);
        if (temp_f->get_func() == "X")
        {
          res_queue.push(token);
        }
        else
        {
          op_stack.push(token);
        }
      }
      else if (token->get_type() == OPERATOR)
      {
        Operator* temp_o = static_cast<Operator*>(token);
        while (!op_stack.empty() && op_stack.top()->get_type() != LPAREN)
        {
          Token* temp_o2 = op_stack.top();
          if (!(precedence(temp_o) < precedence(temp_o2) || precedence(temp_o) == precedence(temp_o2) && temp_o->get_op() != "^"))
          {
            break;
          }
          res_queue.push(temp_o2);
          op_stack.pop();
        }
        op_stack.push(temp_o);
      }
      else if (token->get_type() == LPAREN)
      {
        op_stack.push(token);
      }
      else if (token->get_type() == RPAREN)
      {
        while (op_stack.top()->get_type() != LPAREN)
        {
          assert(!op_stack.empty());
          Token* temp_o2 = op_stack.top();
          res_queue.push(temp_o2);
          op_stack.pop();
        }
        assert(op_stack.top()->get_type() == LPAREN);
        op_stack.pop();
        if (op_stack.top()->get_type() == FUNCTION)
        {
          Token* temp_f = op_stack.top();
          res_queue.push(temp_f);
          op_stack.pop();
        }
      }
      queue.pop();
    }
    while (!op_stack.empty())
    {
      assert(op_stack.top()->get_type() != LPAREN);
      Token* temp_t = op_stack.top();
      res_queue.push(temp_t);
      op_stack.pop();
    }
    return res_queue;
  }
private:
  Queue<Token*> queue;
};

#endif //SHUNTING_YARD_H