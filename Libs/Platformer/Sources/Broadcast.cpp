/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Broadcast
*/

#include "Broadcast.hpp"
#include "Systems.hpp"

Broadcast::Broadcast()
{
    _registry.registerComponent<Health>();
    _registry.registerComponent<Velocity>();
    _registry.registerComponent<Position>();
    _registry.registerComponent<Name>();
    _registry.registerComponent<Clock>();
    _registry.registerComponent<Input>();
    _registry.registerComponent<SpriteFrame>();
    _registry.registerComponent<Damage>();
    _registry.registerComponent<Collider>();
    _registry.registerComponent<Color>();
    _registry.registerComponent<returnValue>();
    _registry.registerComponent<Clickable>();
    _registry.registerComponent<RectangleShape>();

    _window.create(sf::VideoMode(1920, 1080), "Platformer with ECS");
    _window.setFramerateLimit(60);
}

Broadcast::~Broadcast()
{

}

void Broadcast::display(void)
{
    if (_broadcast == MENU)
        _menu.display(_registry, _window);
    if (_broadcast == OPTION)
        _options.display(_registry, _window);
    if (_broadcast == GAME) {
        _game.Systems(_registry);
        _game.display(_registry, _window);
    }
}

void Broadcast::event(void)
{
    if (_broadcast == MENU)
        _broadcast = _menu.event(_registry, _event, _window);
    if (_broadcast == OPTION)
        _broadcast = _options.event(_registry, _event, _window);
    if (_broadcast == GAME)
        _broadcast = _game.event(_registry, _event, _window);
}

void Broadcast::run(void)
{
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _window.close();
            }
            this->event();
        }
        _window.clear();
        this->display();
        _window.display();
        if (_broadcast == QUIT)
            _window.close();
    }
}