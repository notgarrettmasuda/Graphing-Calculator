#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <vector>


#include "includes/shunting_yard/shunting_yard.h"
#include "includes/rpn/rpn.h"
#include "includes/line/line.h"
#include "includes/button/button.h"
#include "includes/textbox/textbox.h"
#include "includes/tokenator/tokenator.h"


using namespace std;

int main()
{
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                                                      "Graphing Calculator");
    //
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third arguments to set style
    //of the window: resize, fullscreen etc.
    //
    //or...
    // you could do this:
    //sf::RenderWindow window;
    //window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
    //                                                  "SFML window!");
    //

    window.setFramerateLimit(30);

    //this is where we keep all the shapes.
    //sf::RectangleShape shapeArray[GRID_HEIGHT][GRID_WIDTH];


    // call it once, after creating the window
    window.setVerticalSyncEnabled(true);
    //Application runs at the same freq as monitor

    //. . . . . . . SHAPES ............
    //this is how you would declare and manipulate shapes:
    sf::CircleShape circle(250.f);
    circle.setFillColor(sf::Color::Green);
    // set a 10-pixel wide orange outline
    circle.setOutlineThickness(10);
    circle.setOutlineColor(sf::Color(250, 150, 100));
    //circle.move(sf::Vector2f(200,300));


    // define a 120x50 rectangle
    sf::RectangleShape rectangle(sf::Vector2f(10, 10));
    rectangle.move(sf::Vector2f(35 + 398, ((sin(1) * 35) + 398)));
    rectangle.setFillColor(sf::Color::Magenta);
    // change the size to 100x100
    //rectangle.setSize(sf::Vector2f(10, 10));
    //. . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    //X Axis
    sf::RectangleShape x_axis(sf::Vector2f(750.f, 1.f));
    x_axis.rotate(90.f);
    x_axis.move(sf::Vector2f((SCREEN_WIDTH / 2) - 100, 50));

    //Y Axis
    sf::RectangleShape y_axis(sf::Vector2f(750.f, 1.f));
    y_axis.move(sf::Vector2f(0, SCREEN_HEIGHT / 2));


    sf::Font font;
    font.loadFromFile("../../arial.ttf");
    sf::Text y_label;
    y_label.setFont(font); 
    y_label.setString("y");
    y_label.setCharacterSize(24);
    y_label.move(sf::Vector2f((SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 10) - 5, 0));

    sf::Text x_label;
    x_label.setFont(font); 
    x_label.setString("x");
    x_label.setCharacterSize(24);
    x_label.move(sf::Vector2f(SCREEN_WIDTH - (SCREEN_WIDTH / 4), (SCREEN_HEIGHT / 2) - 15));
    
    sf::Text functions_label;
    functions_label.setFont(font);
    functions_label.setString("Functions:");
    functions_label.setCharacterSize(18);
    functions_label.setPosition(SCREEN_WIDTH - 150, 75);

    Line y_line;

    Button zoom_in(10, 10, 50, 50, &font, "+", sf::Color(150, 150, 150), sf::Color(100, 100, 100), sf::Color(50, 50, 50));

    Button zoom_out(70, 10, 50, 50, &font, "-", sf::Color(150, 150, 150), sf::Color(100, 100, 100), sf::Color(50, 50, 50));

    Button y_line_delete_b;

    Textbox y_textbox(SCREEN_WIDTH - 200, 20, 24, true, font, 20);
    
    Button y_button(SCREEN_WIDTH - 200, 10, 190, 50, &font, "", sf::Color(150, 150, 150), sf::Color(100, 100, 100), sf::Color(50, 50, 50));

    Button reset_all(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 60, 190, 50, &font, "RESET ALL", sf::Color(150, 150, 150), sf::Color(100, 100, 100), sf::Color(50, 50, 50));

    //Button test(SCREEN_WIDTH - 200, 100, 190, 50, &font, "", sf::Color(150, 150, 150), sf::Color(100, 100, 100), sf::Color(50, 50, 50));

    vector<Line> lines;

    double zoom = 1;

    vector<Button> delete_lines;
    // run the program as long as the window is open
    // this is your main loop:
    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        //go through all the pending events: keyboard, mouse, close, resize, etc.
        //pollEvent and waitEvent are the only two functions that can fill event
        while (window.pollEvent(event))//or waitEvent: EVENT LOOP
        {
            // check the type of the event...
            switch (event.type)
            {
            // window closed
            // "close requested" event: we close the window
            case sf::Event::Closed:
                cout<<"close event was encountered!"<<endl;
                window.close();
                break;

            case sf::Event::TextEntered:
                y_textbox.typed_on(event);

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left && !y_button.is_pressed()) 
                {
                    y_textbox.setSelected(false);
                }

            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    if (y_textbox.get_text().length() > 0)
                    {
                        if (lines.size() < 9)
                        {
                            string y_function = y_textbox.get_text();
                            int delete_button_y_coord = 110 + (lines.size() * 70);
                            y_line_delete_b = Button(SCREEN_WIDTH - 200, delete_button_y_coord, 190, 50, &font, y_function, sf::Color(160, 210, 187), sf::Color(110, 160, 137), sf::Color(60, 110, 87));
                            Queue<Token *> infix = tokenator(y_function);
                            y_line = Line(infix, -350, 350, zoom); 
                            lines.push_back(y_line);
                            delete_lines.push_back(y_line_delete_b);
                        }
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    window.close();
                }
            default:
                continue;

            }
        }
        if (y_button.is_pressed())
        {
            y_textbox.setSelected(true);
        }
        else if (reset_all.is_pressed())
        {
            lines.clear();
            zoom = 1;
        }
        else if (zoom_in.is_pressed())
        {
            zoom *= 2;
            for (int i = 0; i < lines.size(); i++)
            {
                string temp = delete_lines[i].get_string();
                Queue<Token *> infix = tokenator(temp);
                lines[i] = Line(infix, -350, 350, zoom);
            }
        }
        else if (zoom_out.is_pressed())
        {
            zoom *= 0.5;
            for (int i = 0; i < lines.size(); i++)
            {
                string temp = delete_lines[i].get_string();
                Queue<Token *> infix = tokenator(temp);
                lines[i] = Line(infix, -350, 350, zoom);
            }
        }
        for (int i = 0; i < lines.size(); i++)
        {
            if (delete_lines[i].is_pressed())
            {
                while (delete_lines[i].is_pressed())
                {
                    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    delete_lines[i].update(mouse_pos);
                }
                lines.erase(lines.begin() + i);
                delete_lines.erase(delete_lines.begin() + i);
                for (int j = i; i < lines.size(); i++)
                {
                    int delete_button_y_coord = 110 + (i * 70);
                    delete_lines[i].update_position(SCREEN_WIDTH - 200, delete_button_y_coord);
                }
            }
        }

        // you HAVE TO clear your window on every iteration of this while.
        window.clear();

        //window.draw(circle); //draw the circle on the window
        //window.draw(rectangle);
        sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        window.draw(x_axis);
        window.draw(y_axis);
        window.draw(y_label);
        window.draw(x_label);
        window.draw(functions_label);
        for (int i = 0; i < lines.size(); i++)
        {
            lines[i].draw(window);
            delete_lines[i].update(mouse_pos);
            delete_lines[i].draw(window);
        }
        y_button.update(mouse_pos);
        y_button.draw(window);
        zoom_in.update(mouse_pos);
        zoom_in.draw(window);
        zoom_out.update(mouse_pos);
        zoom_out.draw(window);
        reset_all.update(mouse_pos);
        reset_all.draw(window);
        y_textbox.draw(window);
        window.display();
    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}