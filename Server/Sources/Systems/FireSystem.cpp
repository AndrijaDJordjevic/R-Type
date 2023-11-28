/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** FireSystem
*/

#include "Systems.hpp"
#include "Registry.hpp"

void PlayerFireSimpleProjectile(Position &p)
{
    char str[1024] = "Player Bullet";

    size_t entity = Registry::getCurrentRegitry().spawnEntity();
    Registry::getCurrentRegitry().emplaceComponent<Id>(entity, entity, entity);
    Registry::getCurrentRegitry().emplaceComponent<Position>(entity, p._x, p._y);
    Registry::getCurrentRegitry().emplaceComponent<Velocity>(entity, 20, 0);
    Registry::getCurrentRegitry().emplaceComponent<Damage>(entity, 10);
    Registry::getCurrentRegitry().emplaceComponent<Collider>(entity, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y);
    Registry::getCurrentRegitry().emplaceComponent<SpriteFrame>(entity, 2);
    Registry::getCurrentRegitry().emplaceComponent<Health>(entity, 0);
    Registry::getCurrentRegitry().emplaceComponent<Name>(entity, str);
    Registry::getCurrentRegitry().emplaceComponent<Deleted>(entity, 0);
    Registry::getCurrentRegitry().emplaceComponent<Projectile>(entity, 0);
}

void MonsterFireSimpleProjectile(Position &p, SpriteFrame &f)
{
    size_t entity = Registry::getCurrentRegitry().spawnEntity();
    Registry::getCurrentRegitry().emplaceComponent<Id>(entity, entity, entity);
    Registry::getCurrentRegitry().emplaceComponent<Position>(entity, p._x, p._y);
    Registry::getCurrentRegitry().emplaceComponent<Velocity>(entity, 0, PROJECTILE_VELOCITY_MONSTER);
    Registry::getCurrentRegitry().emplaceComponent<Damage>(entity, 1);
    Registry::getCurrentRegitry().emplaceComponent<Collider>(entity, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y);
}

void CheckProjectileOutOfMap(Id &i, Position &p, Damage &d, Deleted &de)
{
    if (p._x > 2000 || p._y > 2000 || p._x < 0 || p._y < 0)
        de._Deleted = 1;
}