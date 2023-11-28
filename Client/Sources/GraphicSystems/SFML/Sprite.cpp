/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** sprite
*/

#include "Sprite.hpp"
#include <SFML/Graphics.hpp>

Sprite::Sprite(std::string path, sf::Vector2i rectDim, anchor anchor)
{
    _isLoaded = false;
    if (!_texture.loadFromFile(path))
        return;
    _isLoaded = true;
    _rect = sf::IntRect(0, 0, rectDim.x, rectDim.y);
    setTexture(_texture);
    setTextureRect(sf::IntRect(0, 0, rectDim.x, rectDim.y));
    _textureDim = _texture.getSize();
    setAnchor(anchor);
}

void Sprite::setAnchor(anchor anchor)
{
    sf::FloatRect dim = getLocalBounds();

    if (anchor == TOPLEFT) {
        setOrigin(0, 0);
    } else if (anchor == TOPRIGHT) {
        setOrigin(dim.width, 0);
    } else if (anchor == BOTTOMLEFT) {
        setOrigin(0, dim.height);
    } else if (anchor == BOTTOMRIGHT) {
        setOrigin(dim.width, dim.height);
    } else if (anchor == CENTER) {
        setOrigin(dim.left + dim.width / 2.0f, dim.top + dim.height / 2.0f);
    }
}

void Sprite::moveRectH(int x)
{
    if (x == -1) {
        if (_rect.left + _rect.width >= (int) _textureDim.x)
            _rect.left = 0;
        else
            _rect.left += _rect.width;
    } else {
        if (x + _rect.width <= (int) _textureDim.x)
            _rect.left = x;
    }
    setTextureRect(_rect);
}

void Sprite::moveRectV(int y)
{
    if (y == -1) {
        if (_rect.top + _rect.height >= (int) _textureDim.y)
            _rect.top = 0;
        else
            _rect.top += _rect.height;
    } else {
        if (y + _rect.height <= (int) _textureDim.y)
            _rect.top = y;
    }
    setTextureRect(_rect);
}

sf::IntRect Sprite::getRect() const
{
    return _rect;
}

bool Sprite::isLoaded() const
{
    return _isLoaded;
}
