/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** graphicComponents
*/

#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <variant>
#include "SpritesProperties.hpp"
#include "KeysCode.hpp"

struct Position {
    int x;
    int y;
};

struct Velocity {
    int x;
    int y;
};

struct ColorRGBA {
    int r;
    int g;
    int b;
    float a;
};

struct SpriteData {
    std::string path;
    std::pair<int, int> sheetSize;
    std::pair<int, int> rectPos;
    std::pair<int, int> rectDim;
};

struct ShapeData {
    std::vector<std::pair<int, int>> points;
};

struct TextData {
    std::string text;
    std::string fontPath;
    int fontSize;
};

struct Drawable {
    bool isVisible;
    std::pair<int, int> scale;
    float rotation;
    ColorRGBA color;
    std::variant<SpriteData, ShapeData, TextData> data;
};

struct SpriteRectMovement {
    int x;
    int y;
    float delay;
    float lastRefresh;
};

struct KeysPressed {
    std::unordered_map<KeysCode, bool> data;
    bool windowClosed;

    KeysPressed() {
        for (int i = 0; i < KeyCount; ++i) {
            data[static_cast<KeysCode>(i)] = false;
        }
        windowClosed = false;
    }
};

struct Background {};

struct Middleground {};

struct Foreground {};
