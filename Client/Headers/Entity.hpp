/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** entity
*/

#pragma once

#include <iostream>

struct Entity {
    int x;
    int y;
    int spriteType;
    std::string name;
    int velocityX;
    int velocityY;
    int hp;
    int deleted;

    Entity() = default;
};

enum EntityType {
    SPRITE,
    SHAPE,
    TEXT,
};

enum LayerType {
    BACKGROUND,
    MIDDLEGROUND,
    FOREGROUND,
};
