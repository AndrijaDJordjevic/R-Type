/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** igraphicsystem
*/

#pragma once

#include "Components.hpp"
#include "GraphicComponents.hpp"
#include "Clock.hpp"
#include <variant>
#include <memory>

class IGraphicSystem {
    public:
        virtual ~IGraphicSystem() = default;
        // draw systems
        virtual void drawBackground(Position &pos, Drawable &drawable, Background &layer) = 0;
        virtual void drawMiddleground(Position &pos, Drawable &drawable, Middleground &layer) = 0;
        virtual void drawForeground(Position &pos, Drawable &drawable, Foreground &layer) = 0;
        // draw sub system
        virtual void draw(Position &pos, Drawable &drawable) = 0;
        // key detection system
        virtual void detectKeys(KeysPressed &keysPressed) = 0;
        // update systems
        virtual void updateSprites(Drawable &drawable, SpriteRectMovement &movement) = 0;
        // other
        virtual void updatePositions(Position &pos, Velocity &vel) = 0;
        virtual void clear() = 0;
        virtual void display() = 0;
        virtual std::unordered_map<int, SpriteData> getSpritesProperties() = 0;
};

class AGraphicSystem : IGraphicSystem {
    public:
        AGraphicSystem() = default;
        AGraphicSystem(std::shared_ptr<Clock> clock);
        //draw systems
        void drawBackground(Position &pos, Drawable &drawable, Background &layer) override;
        void drawMiddleground(Position &pos, Drawable &drawable, Middleground &layer) override;
        void drawForeground(Position &pos, Drawable &drawable, Foreground &layer) override;
        // draw sub systems
        void draw(Position &pos, Drawable &drawable) override;
        // key detection system
        void detectKeys(KeysPressed &keysPressed) override;
        // update systems
        void updateSprites(Drawable &drawable, SpriteRectMovement &movement) override;
        void updatePlayers(Drawable &drawable, SpriteRectMovement &movement, Velocity &vel);
        //other
        void updatePositions(Position &pos, Velocity &vel) override;
        void clear() override;
        void display() override;
        std::unordered_map<int, SpriteData> getSpritesProperties() override;
    protected:
        std::shared_ptr<Clock> _clock;
};
