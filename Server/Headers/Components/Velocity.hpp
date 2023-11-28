/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Velocity
*/

#pragma once

#include "Clock.hpp"

struct Velocity {
    int _xv;
    int _yv;

    Velocity(int xv, int yv) : _xv(xv), _yv(yv){} 
};
