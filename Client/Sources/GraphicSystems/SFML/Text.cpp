/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** text
*/

#include "Text.hpp"

Text::Text(std::string str, std::string fontPath, sf::Vector2f pos, int size, anchor anchor) : sf::Text()
{
    if (!_font.loadFromFile(fontPath))
        return;
    _fontPath = fontPath;
    setFont(_font);
    setString(str);
    setFillColor(sf::Color::Black);
    setCharacterSize(size);
    setAnchor(anchor);
    setPosition(pos);
}

void Text::setAnchor(anchor anchor)
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

void Text::setFontFromPath(std::string path)
{
    if (!_font.loadFromFile(path))
        return;
    _fontPath = path;
    setFont(_font);
}

std::string Text::getFontPath() const
{
    return _fontPath;
}
