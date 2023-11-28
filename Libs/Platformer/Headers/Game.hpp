/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include "Registry.hpp"
    #include "Player.hpp"
    #include "Map.hpp"

class Game {
    public:
        Game();
        ~Game();

        void Systems(Registry &r);
        void display(Registry &r, sf::RenderWindow &window);
        int event(Registry &r, sf::Event &event, sf::RenderWindow &rw);

    private:
        Map _map;
        Player _player;

        bool _loadedGame;
};

#endif /* !GAME_HPP_ */
