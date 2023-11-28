/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "Registry.hpp"
    #include "SFML/Graphics.hpp"
    #include "Systems.hpp"

class Player {
    public:
        Player();
        ~Player();

        void CreatePlayer(Registry &r);

        void Systems(Registry &r);
        void Display(Registry &r, sf::RenderWindow &w);
        void Event(Registry &r, sf::Event &event, sf::RenderWindow &rw);

    private:
        bool _setPlayer;
        float _time;

        size_t _entityPlayer;
        sf::Sprite _Player;
        sf::Texture _Texture;

        int _currentFrame;
        int _frameCount;

        std::function<void(Position &pos, Velocity &v, Input &i)> InputFunc = InputSystems;
        std::function<void(SpriteFrame &s, Clock &c, Input &i)> SpriteFrameRect = UpdateFrameSprite;
        std::function<bool(Position &pos, Collider &col, Input &i, Velocity &v)> CollisionFunc = CollisionSystems;
        std::function<void(Position &pos, Velocity &v, Clock &c)> MoveFunc = MvmtSystems;
};

#endif /* !PLAYER_HPP_ */
