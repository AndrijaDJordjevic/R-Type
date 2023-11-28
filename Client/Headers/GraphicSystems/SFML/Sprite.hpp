/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** sprite
*/

#pragma once

#include "SpritesProperties.hpp"
#include "Anchor.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Sprite : public sf::Sprite
{
    public:
        Sprite() = default;
        Sprite(std::string path, sf::Vector2i rectDim, anchor anchor = CENTER);
        ~Sprite() = default;
        void moveRectH(int height = -1);
        void moveRectV(int width = -1);
        sf::IntRect getRect() const;
        void setAnchor(anchor anchor);
        bool isLoaded() const;
    private:
        sf::Texture _texture;
        sf::IntRect _rect;
        sf::Vector2u _textureDim;
        bool _isLoaded;
};
