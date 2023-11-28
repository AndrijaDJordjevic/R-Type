/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** MvmtSystems
*/

#include "Systems.hpp"

void InputSystems(Position &pos, Velocity &v, Input &i)
{
    v._xv = 0;
    v._yv = 20;

    if (i._jump) {
        v._yv = -20;
    }

    if (i._right) {
        v._xv = 5;
        i._right = false;
    }
    if (i._left) {
        v._xv = -5;
        i._left = false;
    }
}

void MvmtSystems(Position &pos, Velocity &Velocity, Clock &c)
{
    if (c.refresh()) {
        pos._x += Velocity._xv;
    }
    pos._y += Velocity._yv;
}

void ResetMvmtMap(RectangleShape &r, Velocity &v)
{
    v._xv = 0;
}

void MvmtSystemsMapX(RectangleShape &r, Velocity &v)
{
    v._xv += 25;
}

void MvmtSystemsMapMX(RectangleShape &r, Velocity &v)
{
    v._xv += -25;
}
