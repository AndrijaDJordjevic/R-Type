/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** MvmtSystems
*/

#include "Systems.hpp"

void MvmtSystemsBullets(Id &id, Position &pos, Velocity &Velocity, Damage &damage, Deleted &d, Projectile &p)
{
    if (d._Deleted == 1) {
        Registry::getCurrentRegitry().killEntity(id._Index);
        return;
    }
    pos._x += Velocity._xv;
    CheckProjectileOutOfMap(id, pos, damage, d);
}