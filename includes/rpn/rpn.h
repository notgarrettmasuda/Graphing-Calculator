#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <cmath>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

using namespace std;

class RPN
{
public:
  // CTOR
  RPN(){}
  RPN(const Queue<Token*>& input_q)
  {
    queue = input_q;
  }
  
  // save input_q to member variable queue
  void set_input(const Queue<Token *> &input_q)
  {
    queue = input_q;
  }

  // return result from member variable queue
  double operator()(double value = 0)
  {
    return rpn(value);
  }
  // called by operator ()
  double rpn(double value = 0)
  {
    Queue<Token*> copy_queue = queue;
    Stack<double> num_stack;
    while (copy_queue.size() > 0)
    {
      Token* token = copy_queue.front();
      if (token->get_type() == INTEGER)
      {
        Integer* temp_i = static_cast<Integer*>(token);
        num_stack.push(temp_i->get_var());
      }
      else if (token->get_type() == OPERATOR)
      {
        double num1 = num_stack.top();
        num_stack.pop();
        double num2 = num_stack.top();
        num_stack.pop();
        double sum;
        Operator* temp_o = static_cast<Operator*>(token);
        if (temp_o->get_op() == "+")
        {
          sum = num1 + num2;
        }
        else if (temp_o->get_op() == "-")
        {
          sum = num2 - num1;
        }
        else if (temp_o->get_op() == "*")
        {
          sum = num1 * num2;
        }
        else if (temp_o->get_op() == "/")
        {
          sum = num2 / num1;
        }
        else if (temp_o->get_op() == "^")
        {
          sum = pow(num2, num1);
        }
        num_stack.push(sum);
      }
      else if (token->get_type() == FUNCTION)
      {
        Function* temp_f = static_cast<Function*>(token);
        if (temp_f->get_func() == "X")
        {
          num_stack.push(value);
        }
        else if (temp_f->get_func() == "sin")
        {
          double num = num_stack.top();
          num_stack.pop();
          num_stack.push(sin(num));
        }
        else if (temp_f->get_func() == "cos")
        {
          double num = num_stack.top();
          num_stack.pop();
          num_stack.push(cos(num));
        }
        else if (temp_f->get_func() == "tan")
        {
          double num = num_stack.top();
          num_stack.pop();
          num_stack.push(tan(num));
        }
        else if (temp_f->get_func() == "asin")
        {
          double num = num_stack.top();
          num_stack.pop();
          num_stack.push(asin(num));
        }
        else if (temp_f->get_func() == "acos")
        {
          double num = num_stack.top();
          num_stack.pop();
          num_stack.push(acos(num));
        }
        else if (temp_f->get_func() == "atan")
        {
          double num = num_stack.top();
          num_stack.pop();
          num_stack.push(atan(num));
        }
        else if (temp_f->get_func() == "max")
        {
          double num1 = num_stack.top();
          num_stack.pop();
          double num2 = num_stack.top();
          num_stack.pop();
          num_stack.push(max(num1, num2));
        }
        else if (temp_f->get_func() == "min")
        {
          double num1 = num_stack.top();
          num_stack.pop();
          double num2 = num_stack.top();
          num_stack.pop();
          num_stack.push(min(num1, num2));
        }
      }
      copy_queue.pop();
    }
    if (num_stack.size() == 1)
    {
      double res = num_stack.top();
      return res;
    }
    else
    {
      //too many operands to calculate
      assert(num_stack.size() > 1);
    }
  }

private:
  Queue<Token*> queue;
};



#endif //RPN_H