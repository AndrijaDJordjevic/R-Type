/*
** EPITECH PROJECT, 2023
** client
** File description:
** components
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <chrono>
#include "SpritesProperties.hpp"

struct HP {
    int value;
};

struct Inputs {
    bool left;
    bool right;
    bool up;
    bool down;
};
