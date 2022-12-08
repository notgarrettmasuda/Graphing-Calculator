#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace std;

#define DELETE_KEY 8
#define ENTER_KEY 13

class Textbox
{
    public:
        Textbox(){}
        Textbox(float x, float y,int size, bool selected, sf::Font &font, int lim)
        {
            textbox.setPosition(sf::Vector2f(x, y));
            textbox.setCharacterSize(size);
            textbox.setFillColor(sf::Color::White);
            is_selected = selected;
            textbox.setFont(font);
            limit = lim;
            if (selected)
            {
                textbox.setString("_");
            }
            else
            {
                textbox.setString("");
            }
        }

        void setSelected(bool selected)
        {
            is_selected = selected;
            if (!selected && text.str().length() > 0)
            {
                string temp = text.str();
                string res = "";
                for (int i = 0; i < temp.length(); i++)
                {
                    res += temp[i];
                }
                textbox.setString(res);
            }
        }

        string get_text()
        {
            return text.str();
        }

        void draw(sf::RenderWindow &_window)
        {
            _window.draw(textbox);
        }

        void typed_on(sf::Event user_input)
        {
            if (is_selected)
            {
                int char_typed = user_input.text.unicode;
                if (char_typed < 128)
                {
                    if (has_limit)
                    {
                        if (text.str().length() <= limit)
                        {
                            input_log(char_typed);
                        }
                        else if (text.str().length() > limit && char_typed == DELETE_KEY)
                        {
                            delete_last_char();
                        }
                    }
                    else
                    {
                        input_log(char_typed);
                    }
                }
            }
        }

    private:
        sf::Text textbox;
        ostringstream text;
        bool is_selected = false;
        bool has_limit = true;
        int limit;

        void input_log(int char_typed)
        {
            if (char_typed != DELETE_KEY && char_typed != ENTER_KEY)
            {
                text << static_cast<char>(char_typed);
            }
            else if (char_typed == DELETE_KEY)
            {
                if (text.str().length() > 0)
                {
                    delete_last_char();
                }
            }
            textbox.setString(text.str() + "_");
        }

        void delete_last_char()
        {
            string temp = text.str();
            string res = "";
            for (int i = 0; i < temp.length() - 1; i++)
            {
                res += temp[i];
            }
            text.str("");
            text << res;

            textbox.setString(text.str());
        }
};

#endif