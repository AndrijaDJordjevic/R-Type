/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Broadcast
*/

#ifndef BROADCAST_HPP_
    #define BROADCAST_HPP_

    #include "Game.hpp"
    #include "Options.hpp"
    #include "Menu.hpp"
    #include "Registry.hpp"

    #include "SFML/Graphics.hpp"

enum {
    MENU,
    OPTION,
    GAME,
    EXIT,
    QUIT,
};

class Broadcast {
    public:
        Broadcast();
        ~Broadcast();

        void display(void);
        void event(void);
        void run(void);

    private:
        Registry _registry;
        sf::RenderWindow _window;
        sf::Event _event;
        int _broadcast = 0;

        Game _game;
        Options _options;
        Menu _menu;
};

#endif /* !BROADCAST_HPP_ */
