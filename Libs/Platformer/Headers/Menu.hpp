/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include "Registry.hpp"
    #include "SFML/Graphics.hpp"

class Menu {
    public:
        Menu();
        ~Menu();

        void display(Registry &r, sf::RenderWindow &window);
        int event(Registry &r, sf::Event &event, sf::RenderWindow &rw);

    private:
        sf::Font font;
        sf::Text playText;
        sf::Text optionText;
        sf::Text exitText;

        sf::RectangleShape playButton;
        sf::RectangleShape optionButton;
        sf::RectangleShape exitButton;
};

#endif /* !MENU_HPP_ */
