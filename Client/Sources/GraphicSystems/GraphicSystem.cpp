/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** graphic system
*/

#include "GraphicSystem.hpp"

AGraphicSystem::AGraphicSystem(std::shared_ptr<Clock> clock) : _clock(clock) {}

// draw systems
void AGraphicSystem::drawBackground(Position &pos, Drawable &drawable, Background &layer)
{
    draw(pos, drawable);
}

void AGraphicSystem::drawMiddleground(Position &pos, Drawable &drawable, Middleground &layer)
{
    draw(pos, drawable);
}

void AGraphicSystem::drawForeground(Position &pos, Drawable &drawable, Foreground &layer)
{
    draw(pos, drawable);
}

// draw sub systems
void AGraphicSystem::draw(Position &pos, Drawable &drawable) {};

// key detection system
void AGraphicSystem::detectKeys(KeysPressed &keysPressed) {};

// update systems
void AGraphicSystem::updateSprites(Drawable &drawable, SpriteRectMovement &movement)
{
    if (std::holds_alternative<SpriteData>(drawable.data)) {
        if (_clock->canUpdate(movement.delay, movement.lastRefresh)) {
            SpriteData &data = std::get<SpriteData>(drawable.data);
            if (data.rectPos.first + movement.x + data.rectDim.first <= data.sheetSize.first)
                data.rectPos.first += movement.x;
            else
                data.rectPos.first = 0;
            if (data.rectPos.second + movement.y + data.rectDim.second <= data.sheetSize.second)
                data.rectPos.second += movement.y;
            else
                data.rectPos.second = 0;
        }
    }
}

// other
void AGraphicSystem::updatePositions(Position &pos, Velocity &vel)
{
    pos.x += vel.x;
    pos.y += vel.y;
}

void AGraphicSystem::clear() {};

void AGraphicSystem::display() {};

std::unordered_map<int, SpriteData> AGraphicSystem::getSpritesProperties()
{
    return std::unordered_map<int, SpriteData>();
};

void AGraphicSystem::updatePlayers(Drawable &drawable, SpriteRectMovement &movement, Velocity &vel)
{
    if (std::holds_alternative<SpriteData>(drawable.data)) {
        SpriteData &data = std::get<SpriteData>(drawable.data);
        if (data.path == PLAYER_PATH) {
            if (vel.y > 0)
                data.rectPos.second = 0;
            else if (vel.y < 0)
                data.rectPos.second = data.rectDim.second * 2;
            else
                data.rectPos.second = data.rectDim.second * 1;
        }
    }
}
