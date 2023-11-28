/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** MvmtSystems
*/

#include "Systems.hpp"
#include <cstdlib>
#include <ctime>

void MonsterSpawn()
{
    char str[1024] = "Monster";
    std::srand(std::time(nullptr));
    int randomY = std::rand() % (980 - 100 + 1) + 100;

    size_t entity = Registry::getCurrentRegitry().spawnEntity();
    Registry::getCurrentRegitry().emplaceComponent<Id>(entity, entity, entity);
    Registry::getCurrentRegitry().emplaceComponent<Position>(entity, 2000, randomY);
    Registry::getCurrentRegitry().emplaceComponent<Velocity>(entity, -4, 0);
    Registry::getCurrentRegitry().emplaceComponent<Damage>(entity, 1);
    Registry::getCurrentRegitry().emplaceComponent<Collider>(entity, ENEMY_SIZE_X, ENEMY_SIZE_Y);
    Registry::getCurrentRegitry().emplaceComponent<SpriteFrame>(entity, 3);
    Registry::getCurrentRegitry().emplaceComponent<Health>(entity, 20);
    Registry::getCurrentRegitry().emplaceComponent<Name>(entity, str);
    Registry::getCurrentRegitry().emplaceComponent<Clock>(entity, 2);
    Registry::getCurrentRegitry().emplaceComponent<Deleted>(entity, 0);
}


void SetMonsterVelocity(Velocity &v, Position &pos)
{
}

void MvmtSystemsMonsters(Id &i, Position &pos, Velocity &Velocity, Damage &damage, Clock &clock, Deleted &d)
{
    if (d._Deleted == 1) {
        Registry::getCurrentRegitry().killEntity(i._Index);
        return;
    }
    // SetMonsterVelocity(Velocity, pos);
    pos._x += Velocity._xv;
    pos._y += Velocity._yv;
    if (pos._x <= -50)
        d._Deleted = 1;
}