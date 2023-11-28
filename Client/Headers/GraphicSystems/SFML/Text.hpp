/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** text
*/

#pragma once

#include "Anchor.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Text : public sf::Text {
    public:
        Text() = default;
        Text(std::string text, std::string fontPath, sf::Vector2f pos, int size = 50, anchor anchor = TOPLEFT);
        ~Text() = default;
        void setFontFromPath(std::string path);
        void setAnchor(anchor anchor);
        std::string getFontPath() const;
    private:
        std::string _fontPath;
        sf::Font _font;
};
