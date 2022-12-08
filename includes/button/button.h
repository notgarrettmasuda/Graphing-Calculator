#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

enum button_states{B_DEFAULT = 0, B_HOVER, B_PRESSED};

class Button
{
    public:
        Button() {}
        Button(float x, float y, float width, float height, 
        sf::Font* font, string text, 
        sf::Color default_color, sf::Color hover_color, sf::Color pressed_color)
        {
            button_state = B_DEFAULT;

            shape.setPosition(sf::Vector2f(x, y));
            shape.setSize(sf::Vector2f(width, height));
            
            this->font = font;
            this->text.setFont(*this->font);
            this->text.setString(text);
            this->text.setFillColor(sf::Color::White);
            this->text.setCharacterSize(24);
            double x_pos = shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f;
            double y_pos = shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f;
            this->text.setPosition(x_pos, y_pos);

            this->default_color = default_color;
            this->hover_color = hover_color;
            this->pressed_color = pressed_color;

            shape.setFillColor(this->default_color);
            shape.setOutlineThickness(10);
            shape.setOutlineColor(sf::Color(50, 50, 50));
        }

        const bool is_pressed() const
        {
            if (button_state == B_PRESSED)
            {
                return true;
            }
            return false;
        }

        void draw(sf::RenderWindow &_window)
        {
            _window.draw(shape);
            _window.draw(this->text);
        }
    
        void update(const sf::Vector2f mouse_pos)
        {
            //Default/Idle
            button_state = B_DEFAULT;

            //Hover
            if (shape.getGlobalBounds().contains(mouse_pos))
            {
                button_state = B_HOVER;
                
                //Pressed
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    button_state = B_PRESSED;
                }
            }


            switch (button_state)
            {
                case B_DEFAULT:
                    shape.setFillColor(this->default_color);
                    break;
                
                case B_HOVER:
                    shape.setFillColor(this->hover_color);
                    break;

                case B_PRESSED:
                    shape.setFillColor(this->pressed_color);
                    break;

                default:
                    shape.setFillColor(this->default_color);
                    break;
            }
        }
    
    private:
        short unsigned button_state;

        sf::RectangleShape shape;

        //Text vars;
        sf::Font* font;
        sf::Text text;
        
        //Color vars
        sf::Color default_color;
        sf::Color hover_color;
        sf::Color pressed_color;
};

#endif