/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SfmlSystem
*/

#pragma once

#include "GameProperties.hpp"
#include "GraphicSystem.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "SpritesProperties.hpp"
#include "GraphicComponents.hpp"
#include "Clock.hpp"
#include <unordered_map>

class SfmlSystem : public AGraphicSystem {
    public:
        SfmlSystem(std::shared_ptr<Clock> clock);
        ~SfmlSystem() = default;
        void draw(Position &pos, Drawable &drawable) override;
        void clear() override;
        void display() override;
        void detectKeys(KeysPressed &keysPressed) override;
        std::unordered_map<int, SpriteData> getSpritesProperties() override;
    private:
        void initSpritePalette();
        void initSprite(std::string path, sf::Vector2i size);
        std::unordered_map<std::string, std::shared_ptr<Sprite>> _spritePalette;
        std::unordered_map<int, SpriteData> _spritesData;
        sf::ConvexShape _shape;
        Text _text;
        std::shared_ptr<sf::RenderWindow> _window;
        sf::Vector2i _windowSize;
};
