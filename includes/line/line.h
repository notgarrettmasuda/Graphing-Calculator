#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"

const double RESOLUTION = 35;
const double RADIUS = 2;

using namespace std;

class Line
{
    public:
        Line() {}
        Line(const Queue<Token*>& queue_input, double low_r, double high_r)
        {
            ShuntingYard sy(queue_input);
            Queue<Token*> postfix = sy.postfix();
            RPN rpn;
            rpn.set_input(postfix);
            for(double i = low_r; i < high_r + 1; i += RADIUS / RESOLUTION)
            {
                sf::CircleShape circle;
                circle.setOrigin(-400 + RADIUS, -400 + RADIUS);
                circle.setRadius(RADIUS);
                double x = i * RESOLUTION;
                double y = (rpn(i) * -1) * RESOLUTION;
                if (x <= 350 && y <= 350)
                {
                    circle.setPosition(x, y);
                    circles.push_back(circle);
                }
            }
        }

        void draw(sf::RenderWindow &_window)
        {
            for (int i = 0; i < circles.size(); i++)
            {
                _window.draw(circles[i]);
            }
        }


    private:
        vector<sf::CircleShape> circles;
};


#endif