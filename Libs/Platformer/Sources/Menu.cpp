/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Systems.hpp"

Menu::Menu()
{
    font.loadFromFile("Libs/Platformer/Assets/Minecraft.ttf");

    playText.setFont(font);
    optionText.setFont(font);
    exitText.setFont(font);

    playText.setString("Play"); // Le texte que vous souhaitez afficher
    optionText.setString("Option");
    exitText.setString("Exit");

    playText.setCharacterSize(24); // Taille du texte
    optionText.setCharacterSize(24);
    exitText.setCharacterSize(24);

    playText.setFillColor(sf::Color::Black); // Couleur du texte
    optionText.setFillColor(sf::Color::Black);
    exitText.setFillColor(sf::Color::Black);

    playButton.setSize(sf::Vector2f(200, 50));
    optionButton.setSize(sf::Vector2f(200, 50));
    exitButton.setSize(sf::Vector2f(200, 50));

    playButton.setPosition(300, 200);
    optionButton.setPosition(300, 300);
    exitButton.setPosition(300, 400);

    playButton.setFillColor(sf::Color::Green);
    optionButton.setFillColor(sf::Color::Blue);
    exitButton.setFillColor(sf::Color::Red);
}

Menu::~Menu()
{

}

void Menu::display(Registry &r, sf::RenderWindow &window)
{
    playButton.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 10));
    playButton.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 6));
    sf::FloatRect playBounds = playButton.getGlobalBounds();
    sf::FloatRect textBounds = playText.getLocalBounds();
    playText.setPosition(playBounds.left + (playBounds.width - textBounds.width) / 2, playBounds.top + (playBounds.height - textBounds.height) / 2);

    optionButton.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3));
    optionButton.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 10));
    sf::FloatRect optionBounds = optionButton.getGlobalBounds();
    sf::FloatRect textBoundsoption = optionText.getLocalBounds();
    optionText.setPosition(optionBounds.left + (optionBounds.width - textBoundsoption.width) / 2, optionBounds.top + (optionBounds.height - textBoundsoption.height) / 2);

    exitButton.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 2));
    exitButton.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 10));
    sf::FloatRect exitBounds = exitButton.getGlobalBounds();
    sf::FloatRect exitTextBounds = exitText.getLocalBounds();
    exitText.setPosition(exitBounds.left + (exitBounds.width - exitTextBounds.width) / 2, exitBounds.top + (exitBounds.height - exitTextBounds.height) / 2);

    window.draw(playButton);
    window.draw(optionButton);
    window.draw(exitButton);
    window.draw(playText);
    window.draw(optionText);
    window.draw(exitText);
}

int Menu::event(Registry &r, sf::Event &event, sf::RenderWindow &rw)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(rw);

            if (playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                return 2;
            } else if (optionButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                return 1;
            } else if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                return 4;
            }
        }
    }
    return (0);
}
