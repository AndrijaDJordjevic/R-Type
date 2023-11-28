/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** MvmtSystems
*/

#include "Systems.hpp"

void SetVelocityFromInput(InputInfo &i, Velocity &v, Position &pos)
{
    int velocity = 10;

    if (i._right && pos._x + velocity < 1920)
        v._xv = velocity;
    else if (i._left && pos._x - velocity > 0)
        v._xv = -velocity;
    else
        v._xv = 0;

    if (i._down && pos._y + velocity < 1080)
        v._yv = velocity;
    else if (i._up && pos._y - velocity > 0)
        v._yv = -velocity;
    else 
        v._yv = 0;
}

void MvmtSystems(Id &i, Position &pos, Velocity &v, InputInfo &input, Clock &clock, Deleted &d)
{
    if (d._Deleted == 1 || i._Id == 0) {
        v._xv = 0;
        v._yv = 0;
        pos._x = 0;
        pos._y = 0;
        return;
    }
    SetVelocityFromInput(input, v, pos);
    pos._x += v._xv;
    pos._y += v._yv;
    if (clock.refresh() == true) {
        PlayerFireSimpleProjectile(pos);
    }
}