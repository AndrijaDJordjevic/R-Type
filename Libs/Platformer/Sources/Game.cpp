/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    _loadedGame = false;
}

Game::~Game()
{

}

void Game::Systems(Registry &r)
{
    _map.Systems(r);
    _player.Systems(r);
}

void Game::display(Registry &r, sf::RenderWindow &window)
{
    _map.Display(r, window);
    _player.Display(r, window);
}

int Game::event(Registry &r, sf::Event &event, sf::RenderWindow &rw)
{
    _player.Event(r, event , rw);
    _map.Event(r, event, rw);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return 0;
    return 2;
}