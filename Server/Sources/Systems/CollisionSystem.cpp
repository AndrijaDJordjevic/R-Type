/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** CollisionSystem
*/

#include "Registry.hpp"
#include "Systems.hpp"

#include "Registry.hpp"

static bool CheckCollision(Position &pos1, Collider &col1, Position &pos2, Collider &col2)
{
    int left1 = pos1._x;
    int right1 = pos1._x + col1._width;
    int top1 = pos1._y;
    int bottom1 = pos1._y + col1._height;

    int left2 = pos2._x;
    int right2 = pos2._x + col2._width;
    int top2 = pos2._y;
    int bottom2 = pos2._y + col2._height;

    if (right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2)
        return false;
    return true;
}


void CollisionSystems(Id &i, Damage &d, Position &pos, Collider &col, SpriteFrame &sf)
{
    Registry &registry = Registry::getCurrentRegitry();

    SparseArray<Id> &id = registry.getComponents<Id>();
    SparseArray<Collider> &colliders = registry.getComponents<Collider>();
    SparseArray<Position> &positions = registry.getComponents<Position>();
    SparseArray<Health> &health = registry.getComponents<Health>();
    SparseArray<SpriteFrame> &spriteFrame = registry.getComponents<SpriteFrame>();
    SparseArray<Deleted> &deleted = registry.getComponents<Deleted>();

    for (size_t entity : registry.getEntities()) {
        if (colliders.HasEntity(entity) && positions.HasEntity(entity)) {
            Id &entityId = id[entity];
            Collider &entityCollider = colliders[entity];
            Position &entityPosition = positions[entity];
            Health &entityHealth = health[entity];
            SpriteFrame &entitySpriteFrame = spriteFrame[entity];
            Deleted &entityDeleted = deleted[entity];
            if (sf._spriteFrame != entitySpriteFrame._spriteFrame) {
                if (sf._spriteFrame == 2 && entitySpriteFrame._spriteFrame == 3 && CheckCollision(pos, col, entityPosition, entityCollider)) {
                    std::cout << "Bullet kill monster" << std::endl;
                    entityDeleted._Deleted = 1;
                }
                else if (sf._spriteFrame == 3 && entitySpriteFrame._spriteFrame == 1 && CheckCollision(pos, col, entityPosition, entityCollider)) {
                    std::cout << "MONSTER KILLED THIS SHIP" << std::endl;
                    entityDeleted._Deleted = 1;
                }
            }
        }
     }

}
