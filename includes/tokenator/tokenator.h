#ifndef TOKENATOR_H
#define TOKENATOR_H

#include <iostream>
#include <string>

#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

using namespace std;

Queue<Token *> tokenator(string y_function)
{
    Queue<Token *> res;
    res.push(new Integer(0));
    int index = 0;
    if (y_function[index] != '-')
    {
        res.push(new Operator("+"));
    }
    while (index < y_function.size())
    {
        //Parenthesis
        if (y_function[index] == '(')
        {
            res.push(new LeftParen());
        }
        else if (y_function[index] == ')')
        {
            res.push(new RightParen());
        }

        //Function var
        else if (y_function[index] == 'X')
        {
            res.push(new Function("X"));
        }

        //Operators
        else if (y_function[index] == '+')
        {
            res.push(new Operator("+"));
        }
        else if (y_function[index] == '-')
        {
            res.push(new Operator("-"));
        }
        else if (y_function[index] == '*')
        {
            res.push(new Operator("*"));
        }
        else if (y_function[index] == '/')
        {
            res.push(new Operator("/"));
        }
        else if (y_function[index] == '^')
        {
            res.push(new Operator("^"));
        }

        //Functions
        else if (y_function[index] == 's')
        {
            res.push(new Function("sin"));
            index += 2;
        }
        else if (y_function[index] == 'c')
        {
            res.push(new Function("cos"));
            index += 2;
        }
        else if (y_function[index] == 't')
        {
            res.push(new Function("tan"));
            index += 2;
        }
        else if (y_function[index] == 'a')
        {
            index++;
            if (y_function[index] == 's')
            {
                res.push(new Function("asin"));
                index += 2;
            }
            else if (y_function[index] == 'c')
            {
                res.push(new Function("acos"));
                index += 2;
            }
            else if (y_function[index] == 't')
            {
                res.push(new Function("atan"));
                index += 2;
            }
        }
        else if (y_function[index] == 'm')
        {
            index++;
            if (y_function[index] == 'a')
            {
                res.push(new Function("max"));
                index++;
            }
            else if (y_function[index] == 'i')
            {
                res.push(new Function("min"));
                index++;
            }
        }

        //Numbers
        else if (isdigit(y_function[index]))
        {
            string temp = "";
            while (isdigit(y_function[index]) && index < y_function.size())
            {
                temp = temp + y_function[index];
                index++;
            }
            index--;
            double num = stod(temp);
            res.push(new Integer(num));
        }
        else if (y_function[index] == 'p')
        {
            index++;
            if (y_function[index] == 'i')
            {
                res.push(new Integer(M_PI));
            }
        }
        index++;
    }
    return res;
}

#endif