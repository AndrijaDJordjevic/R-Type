/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Game
*/

#pragma once

#include "Components.hpp"
#include "Registry.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"
#include "GraphicComponents.hpp"
#include "Clock.hpp"
#include "GameProperties.hpp"
#include "SpritesProperties.hpp"
#include "Entity.hpp"
#include <vector>
#include <memory>
#include <optional>

class Game {
    public:
        Game() = default;
        Game(std::shared_ptr<Registry> registry);
        ~Game() = default;
        void updateData(int id, Entity entity);
        std::optional<Inputs> refresh();
        void display();
        void endOfGame(bool win);
    private:
        bool fillInputs(Inputs &inputs, KeysPressed &keysPressed);
        int createDefaultEntity(Position pos, Drawable drawable, LayerType layer);
        void initEntities();
        std::shared_ptr<Registry> _registry;
        std::unique_ptr<AGraphicSystem> _graphicSystem;
        size_t _gameIndex;
        Clock _clock;
        std::unordered_map<int, int> _serverEntities; // id, registry index
        //graphic systems
        std::function<void(Position &pos, Velocity &vel)> _UpdatePositionsFunc;
        std::function<void(Drawable &drawable, SpriteRectMovement &movement, Velocity &vel)> _UpdatePlayersFunc;
        std::function<void(Drawable &drawable, SpriteRectMovement &movement)> _UpdateSpritesFunc;
        std::function<void(Position &pos, Drawable &drawable, Background &layer)> _DrawBackgroundFunc;
        std::function<void(Position &pos, Drawable &drawable, Middleground &layer)> _DrawMiddlegroundFunc;
        std::function<void(Position &pos, Drawable &drawable, Foreground &layer)> _DrawForegroundFunc;
        std::function<void(KeysPressed &keysPressed)> _DetectKeysFunc;
};

