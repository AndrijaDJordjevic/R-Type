/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Options
*/

#include "Options.hpp"

Options::Options()
{
    font.loadFromFile("Libs/Platformer/Assets/Minecraft.ttf");

    soundText.setFont(font);
    sizeText.setFont(font);
    returnText.setFont(font);

    soundButton.setSize(sf::Vector2f(200, 50));
    sizeButton.setSize(sf::Vector2f(200, 50));
    returnButton.setSize(sf::Vector2f(200, 50));

    soundButton.setPosition(300, 500);
    sizeButton.setPosition(300, 600);
    returnButton.setPosition(300, 700);

    soundButton.setFillColor(sf::Color::Blue);
    sizeButton.setFillColor(sf::Color::Red);
    returnButton.setFillColor(sf::Color::Green);

    soundText.setCharacterSize(28);
    sizeText.setCharacterSize(28);
    returnText.setCharacterSize(28);

    soundText.setFillColor(sf::Color::White);
    sizeText.setFillColor(sf::Color::White);
    returnText.setFillColor(sf::Color::White);

    soundText.setString("Sound on");
    sizeText.setString("Change Size: 1920x1080");
    returnText.setString("Return");
}

Options::~Options()
{
}

void Options::display(Registry &r, sf::RenderWindow &window)
{
    soundButton.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 10));
    soundButton.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 6));
    sf::FloatRect playBounds = soundButton.getGlobalBounds();
    sf::FloatRect textBounds = soundText.getLocalBounds();
    soundText.setPosition(playBounds.left + (playBounds.width - textBounds.width) / 2, playBounds.top + (playBounds.height - textBounds.height) / 2);

    sizeButton.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3));
    sizeButton.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 10));
    sf::FloatRect optionBounds = sizeButton.getGlobalBounds();
    sf::FloatRect textBoundsoption = sizeText.getLocalBounds();
    sizeText.setPosition(optionBounds.left + (optionBounds.width - textBoundsoption.width) / 2, optionBounds.top + (optionBounds.height - textBoundsoption.height) / 2);

    returnButton.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 2));
    returnButton.setSize(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 10));
    sf::FloatRect exitBounds = returnButton.getGlobalBounds();
    sf::FloatRect returnTextBounds = returnText.getLocalBounds();
    returnText.setPosition(exitBounds.left + (exitBounds.width - returnTextBounds.width) / 2, exitBounds.top + (exitBounds.height - returnTextBounds.height) / 2);

    window.draw(soundButton);
    window.draw(returnButton);
    window.draw(sizeButton);

    window.draw(soundText);
    window.draw(sizeText);
    window.draw(returnText);
}

int Options::event(Registry &r, sf::Event &event, sf::RenderWindow &rw)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(rw);

            if (soundButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                if (soundText.getString() == "Sound on")
                    soundText.setString("Sound off");
                else
                    soundText.setString("Sound on");
            } else if (sizeText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                if (sizeText.getString() == "Change Size: 1920x1080") {
                    sizeText.setString("Change Size: 800x600");
                    rw.setSize(sf::Vector2u(800, 600));
                } else {
                    sizeText.setString("Change Size: 1920x1080");
                    rw.setSize(sf::Vector2u(1920, 1080));
                }
            } else if (returnButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                return 0;
            }
        }
    }
    return 1;
}