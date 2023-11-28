/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Player
*/

#include "Player.hpp"

Player::Player()
{
    _Texture.loadFromFile("Libs/Platformer/Assets/walk.png");
    _Player.setTexture(_Texture);
    _currentFrame = 0;
    _frameCount = 0;
    _setPlayer = false;
    _time = 0;
}

Player::~Player()
{
}

void Player::CreatePlayer(Registry &r)
{
    _entityPlayer = r.spawnEntity();
    r.emplaceComponent<Position>(_entityPlayer, 500, 750);
    r.emplaceComponent<Velocity>(_entityPlayer, 0, 0);
    r.emplaceComponent<Input>(_entityPlayer, false, false, false, false ,false);
    r.emplaceComponent<Collider>(_entityPlayer, 50, 50);
    r.emplaceComponent<SpriteFrame>(_entityPlayer, 0, 48, 48);
    r.emplaceComponent<Clock>(_entityPlayer, 0.02);
    _setPlayer = true;
}

void Player::Systems(Registry &r)
{
    if (!_setPlayer)
        CreatePlayer(r);

    if (r.getComponents<Input>()[_entityPlayer]._jump) {
        _time++;
        if (_time > 10) {
            r.getComponents<Input>()[_entityPlayer]._jump = false;
            _time = 0;
        }
    }

    r.Exec(SpriteFrameRect);
    r.Exec(InputFunc);
    if (!r.Exec(CollisionFunc))
        r.Exec(MoveFunc);
}

void Player::Display(Registry &r, sf::RenderWindow &w)
{
    _Player.setPosition(sf::Vector2f(r.getComponents<Position>()[_entityPlayer]._x, r.getComponents<Position>()[_entityPlayer]._y));
    _Player.setTextureRect(sf::IntRect(49 * r.getComponents<SpriteFrame>()[_entityPlayer]._spriteFrame, 0, 48, 48));
    w.draw(_Player);
}

void Player::Event(Registry &r, sf::Event &event, sf::RenderWindow &rw)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        r.getComponents<Input>()[_entityPlayer]._left = true;
        _Player.setScale(sf::Vector2f(-1, 1));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        r.getComponents<Input>()[_entityPlayer]._right = true;
        _Player.setScale(sf::Vector2f(1, 1));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !r.getComponents<Input>()[_entityPlayer]._jump) {
        r.getComponents<Input>()[_entityPlayer]._jump = true;
    }
}