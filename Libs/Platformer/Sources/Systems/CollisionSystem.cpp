/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** CollisionSystem
*/

#include "Registry.hpp"
#include "Systems.hpp"
#include "Registry.hpp"

#include <iostream>

static bool CheckCollision(Position &pos1, Collider &col1, Position &pos2, Collider &col2, Velocity &playerVelocity)
{
    Position currentPositionPlayer = pos1;
    Position currentPositionObject = pos2;

    int left1 = currentPositionPlayer._x + playerVelocity._xv;
    int right1 = left1 + col1._width;
    int top1 = currentPositionPlayer._y + playerVelocity._yv;
    int bottom1 = top1 + col1._height;

    int left2 = currentPositionObject._x;
    int right2 = left2 + col2._width;
    int top2 = currentPositionObject._y;
    int bottom2 = top2 + col2._height;

    bool collisionDetected = !(right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2);

    if (collisionDetected) {
        if (playerVelocity._yv > 0 && top1 <= bottom2) {
            playerVelocity._yv = 0;
            currentPositionPlayer._y = bottom2 - 40;
            return false;
        }

        if (playerVelocity._xv > 0 && left1 <= right2) {
            playerVelocity._xv = 0;
            currentPositionPlayer._x = right2;
        }

        if (playerVelocity._xv < 0 && right1 >= left2) {
            playerVelocity._xv = 0;
            currentPositionPlayer._x = left2 - col1._width;
        }
    }

    return collisionDetected;
}


bool CollisionSystems(Position &pos, Collider &col, Input &i, Velocity &v)
{
    Registry &registry = Registry::getCurrentRegitry();
    
    SparseArray<Collider> &colliders = registry.getComponents<Collider>();
    SparseArray<Position> &positions = registry.getComponents<Position>();
    SparseArray<Input> &input = registry.getComponents<Input>();

     for (size_t entityId : registry.getEntities()) {
        if (colliders.HasEntity(entityId) && positions.HasEntity(entityId) && !input.HasEntity(entityId)) {
            Collider &entityCollider = colliders[entityId];
            Position &entityPosition = positions[entityId];
            if (CheckCollision(pos, col, entityPosition , entityCollider, v)) {
                return true;
            }
        }
     }
    return false;
}
