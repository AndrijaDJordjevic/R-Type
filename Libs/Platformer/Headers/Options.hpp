/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Options
*/

#ifndef OPTIONS_HPP_
    #define OPTIONS_HPP_

    #include "Registry.hpp"
    #include "SFML/Graphics.hpp"
    #include <iostream>

class Options {
    public:
        Options();
        ~Options();

        void display(Registry &r, sf::RenderWindow &window);
        int event(Registry &r, sf::Event &event, sf::RenderWindow &rw);
    private:
        sf::Font font;

        sf::RectangleShape soundButton;
        sf::RectangleShape sizeButton;
        sf::RectangleShape returnButton;

        sf::Text soundText;
        sf::Text sizeText;
        sf::Text returnText;
};

#endif /* !OPTIONS_HPP_ */
