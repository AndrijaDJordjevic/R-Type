/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** HealthSystem
*/

#include "Systems.hpp"

void checkLose(Id &i, Damage &d, Position &pos, Collider &col)
{
    Registry &registry = Registry::getCurrentRegitry();
    
    SparseArray<Health> &health = registry.getComponents<Health>();

    bool allPlayersDead = true;

    for (int entityId = 1; entityId <= 4; entityId++) {
        Health &entityHealth = health[entityId];
        if (entityHealth._Health > 0) {
            allPlayersDead = false;
            break;
        }
    }

    if (allPlayersDead == true) {
        std::cout << "GAME OVER" << std::endl;
    }
}
