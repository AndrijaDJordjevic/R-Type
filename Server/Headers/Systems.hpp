/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
    #define SYSTEMS_HPP_

    #include "Registry.hpp"

    #include "Components/Id.hpp"
    #include "Components/Health.hpp"
    #include "Components/Position.hpp"
    #include "Components/Name.hpp"
    #include "Components/SpriteFrame.hpp"
    #include "Components/Velocity.hpp"
    #include "Components/Collider.hpp"
    #include "Components/Damage.hpp"
    #include "Components/InputInfo.hpp"
    #include "Components/Clock.hpp"
    #include "Components/Deleted.hpp"
    #include "Components/Projectile.hpp"

    #define PLAYER_SIZE_X 34
    #define PLAYER_SIZE_Y 15
    #define PROJECTILE_SIZE_X 16
    #define PROJECTILE_SIZE_Y 8
    #define PROJECTILE_VELOCITY_PLAYER   1
    #define PROJECTILE_VELOCITY_MONSTER -1
    #define ENEMY_SIZE_X 32
    #define ENEMY_SIZE_Y 33

    //FireSystems:
    void PlayerFireSimpleProjectile(Position &p);
    void MonsterFireSimpleProjectile(Position &p, SpriteFrame &f);
    void CheckProjectileOutOfMap(Id &i, Position &p, Damage &d, Deleted &de);

    //MovementSystems
    void MvmtSystems(Id &i, Position &pos, Velocity &v, InputInfo &input, Clock &clock, Deleted &d);
    void MvmtSystemsBullets(Id &id, Position &pos, Velocity &Velocity, Damage &damage, Deleted &d, Projectile &p);
    void MvmtSystemsMonsters(Id &i, Position &pos, Velocity &Velocity, Damage &damage, Clock &clock, Deleted &d);
    void SetVelocityFromInput(InputInfo &i, Velocity &v, Position &pos, Deleted &d);

    void MonsterSpawn();

    void CollisionSystems(Id &i, Damage &d, Position &pos, Collider &col, SpriteFrame &sf);

#endif /* !SYSTEMS_HPP_ */
