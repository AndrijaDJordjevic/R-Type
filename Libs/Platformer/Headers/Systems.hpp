/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
    #define SYSTEMS_HPP_

    #include "Registry.hpp"

    #include "Id.hpp"
    #include "Health.hpp"
    #include "Position.hpp"
    #include "Name.hpp"
    #include "SpriteFrame.hpp"
    #include "Velocity.hpp"
    #include "Collider.hpp"
    #include "Damage.hpp"
    #include "Input.hpp"
    #include "Clock.hpp"
    #include "Text.hpp"
    #include "Color.hpp"
    #include "returnValue.hpp"
    #include "Clickable.hpp"
    #include "RectangleShape.hpp"

    //MovementSystems
    void MvmtSystems(Position &pos, Velocity &Velocity, Clock &c);
    void InputSystems(Position &pos, Velocity &v, Input &i);
    void ResetMvmtMap(RectangleShape &r, Velocity &v);
    void MvmtSystemsMapX(RectangleShape &r, Velocity &v);
    void MvmtSystemsMapMX(RectangleShape &r, Velocity &v);
    void SetVelocityFromInput(Input &i, Velocity &v);
    void GravityPlayer(Position &pos, Velocity &Velocity, Clock &c, Input &i);
    bool CollisionSystems(Position &pos, Collider &col, Input &i, Velocity &v);

    //Clock
    void UpdateTime(Clock &c);
    void UpdateFrameSprite(SpriteFrame &s, Clock &c, Input &i);

#endif /* !SYSTEMS_HPP_ */
