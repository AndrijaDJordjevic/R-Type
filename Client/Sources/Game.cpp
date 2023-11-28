/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** Game
*/

#include "Game.hpp"
#include "SfmlSystem.hpp"

//------CONSTRUCTOR
Game::Game(std::shared_ptr<Registry> registry) : _registry(registry), _clock(0.01)
{
    _gameIndex = _registry->spawnEntity();

    // init graphic components
    _registry->registerComponent<Position>();
    _registry->registerComponent<Drawable>();
    _registry->registerComponent<Background>();
    _registry->registerComponent<Middleground>();
    _registry->registerComponent<Foreground>();
    _registry->registerComponent<Velocity>();
    _registry->registerComponent<SpriteRectMovement>();
    //init graphic system
    _graphicSystem = std::make_unique<SfmlSystem>(std::make_shared<Clock>(_clock));
    _UpdatePositionsFunc = [this](Position &pos, Velocity &vel) -> void {_graphicSystem->updatePositions(pos, vel);};
    _UpdatePlayersFunc = [this](Drawable &drawable, SpriteRectMovement &movement, Velocity &vel) -> void {_graphicSystem->updatePlayers(drawable, movement, vel);};
    _UpdateSpritesFunc = [this](Drawable &drawable, SpriteRectMovement &movement) -> void {_graphicSystem->updateSprites(drawable, movement);};
    _DrawBackgroundFunc = [this](Position &pos, Drawable &draw, Background &layer) -> void {_graphicSystem->drawBackground(pos, draw, layer);};
    _DrawMiddlegroundFunc = [this](Position &pos, Drawable &draw, Middleground &layer) -> void {_graphicSystem->drawMiddleground(pos, draw, layer);};
    _DrawForegroundFunc = [this](Position &pos, Drawable &draw, Foreground &layer) -> void {_graphicSystem->drawForeground(pos, draw, layer);};
    _DetectKeysFunc = [this](KeysPressed &keysPressed) -> void {_graphicSystem->detectKeys(keysPressed);};
    //other components
    _registry->registerComponent<HP>();
    _registry->emplaceComponent<HP>(_gameIndex, (HP) {1});
    _registry->registerComponent<KeysPressed>();
    _registry->emplaceComponent<KeysPressed>(_gameIndex, KeysPressed());
    //other
    initEntities();
}

//------UPDATE GAME DATA
int Game::createDefaultEntity(Position pos, Drawable drawable, LayerType layer)
{
    int index = _registry->spawnEntity();

    //set position
    _registry->emplaceComponent<Position>(index, pos);
    //set drawable
    _registry->emplaceComponent<Drawable>(index, drawable);
    //set layer
    if (layer == LayerType::BACKGROUND)
        _registry->emplaceComponent<Background>(index, (Background) {});
    else if (layer == LayerType::MIDDLEGROUND)
        _registry->emplaceComponent<Middleground>(index, (Middleground) {});
    else if (layer == LayerType::FOREGROUND)
        _registry->emplaceComponent<Foreground>(index, (Foreground) {});

    return index;
}

void Game::updateData(int id, Entity entity)
{
    int entityIndex = (_serverEntities.find(id) != _serverEntities.end() ? _serverEntities[id] : -1);
    if (entity.deleted == 1) {
        _registry->getComponents<Drawable>()[entityIndex].isVisible = false;
    }
    SpriteData spriteProperties = _graphicSystem->getSpritesProperties()[entity.spriteType];
    if (entityIndex == -1) {
        entityIndex = createDefaultEntity((Position) {entity.x, entity.y}, (Drawable) {true, {5, 5}, 0, {0, 0, 0, 255}, spriteProperties}, LayerType::MIDDLEGROUND);
        _serverEntities[id] = entityIndex;
        _registry->emplaceComponent<Velocity>(entityIndex, (Velocity) {entity.velocityX, entity.velocityY});
        if (entity.spriteType == SpriteType::PLAYER)
            _registry->emplaceComponent<SpriteRectMovement>(entityIndex, (SpriteRectMovement) {PLAYER_SIZE_X, 0, 0.2, 0});
        else if (entity.spriteType == SpriteType::ENEMY)
            _registry->emplaceComponent<SpriteRectMovement>(entityIndex, (SpriteRectMovement) {ENEMY_SIZE_X, 0, 0.1, 0});
    } else {
        _registry->getComponents<Velocity>()[entityIndex] = (Velocity) {entity.velocityX, entity.velocityY};
        _registry->getComponents<Position>()[entityIndex] = (Position) {entity.x, entity.y};
        std::pair<int, int> rectpos = std::get<SpriteData>(_registry->getComponents<Drawable>()[entityIndex].data).rectPos;
        _registry->getComponents<Drawable>()[entityIndex] = (Drawable) {true, {5, 5}, 0, {0, 0, 0, 255}, (SpriteData) {spriteProperties.path, spriteProperties.sheetSize, rectpos, spriteProperties.rectDim}};
    }
    if (entity.hp > -1)
        _registry->getComponents<HP>()[_gameIndex].value = entity.hp;
}

//------REFRESH GAME
bool Game::fillInputs(Inputs &inputs, KeysPressed &keysPressed)
{
    if (keysPressed.windowClosed) return false;
    inputs.left = keysPressed.data[LEFT];
    inputs.right = keysPressed.data[RIGHT];
    inputs.up = keysPressed.data[UP];
    inputs.down = keysPressed.data[DOWN];
    return true;
}

std::optional<Inputs> Game::refresh()
{
    //Manage Display
    if (_clock.refresh())
        display();

    //Manage inputs
    _registry->Exec(_DetectKeysFunc);
    Inputs inputs;
    if (!fillInputs(inputs, _registry->getComponents<KeysPressed>()[_gameIndex]))
        return std::nullopt;
    return inputs;
}

void Game::display()
{
    _registry->Exec(_UpdatePositionsFunc);
    _registry->Exec(_UpdateSpritesFunc);
    _registry->Exec(_UpdatePlayersFunc);
    _graphicSystem->clear();
    _registry->Exec(_DrawBackgroundFunc);
    _registry->Exec(_DrawMiddlegroundFunc);
    _registry->Exec(_DrawForegroundFunc);
    _graphicSystem->display();
}

//------INIT ENTITIES
void Game::initEntities()
{
    //init background
    SpriteData bg0Data = {CAVE_0_PATH, {CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y}, {0, 0}, {CAVE_SIZE_X, CAVE_SIZE_Y}};
    int background0 = createDefaultEntity({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, {true, {5, 5}, 0, {0, 0, 0, 255}, bg0Data}, LayerType::BACKGROUND);

    SpriteData bg1Data = {CAVE_1_PATH, {CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y}, {0, 0}, {CAVE_SIZE_X, CAVE_SIZE_Y}};
    int background1 = createDefaultEntity({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, {true, {5, 5}, 0, {0, 0, 0, 255}, bg1Data}, LayerType::BACKGROUND);
    _registry->emplaceComponent<SpriteRectMovement>(background1, (SpriteRectMovement) {1, 0, 0.01, 0});

    SpriteData bg2Data = {CAVE_2_PATH, {CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y}, {0, 0}, {CAVE_SIZE_X, CAVE_SIZE_Y}};
    int background2 = createDefaultEntity({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, {true, {5, 5}, 0, {0, 0, 0, 255}, bg2Data}, LayerType::BACKGROUND);
    _registry->emplaceComponent<SpriteRectMovement>(background2, (SpriteRectMovement) {2, 0, 0.01, 0});

    SpriteData bg3Data = {CAVE_3_PATH, {CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y}, {0, 0}, {CAVE_SIZE_X, CAVE_SIZE_Y}};
    int background3 = createDefaultEntity({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, {true, {5, 5}, 0, {0, 0, 0, 255}, bg3Data}, LayerType::BACKGROUND);
    _registry->emplaceComponent<SpriteRectMovement>(background3, (SpriteRectMovement) {3, 0, 0.01, 0});
}

void Game::endOfGame(bool win)
{
    int shadow = createDefaultEntity({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, {true, {1, 1}, 0, {0, 0, 0, 200}, (ShapeData) {{{0, 0}, {WINDOW_SIZE_X, 0}, {WINDOW_SIZE_X, WINDOW_SIZE_Y}, {0, WINDOW_SIZE_Y}}}}, LayerType::FOREGROUND);

    if (win) {
        std::cout << "You win !" << std::endl;
        int text = createDefaultEntity({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, {true, {1, 1}, 0, {255, 255, 255, 255}, (TextData) {"You win !", FONT_PATH, 100}}, LayerType::FOREGROUND);
    }
    else {
        std::cout << "You lose !" << std::endl;
        int text = createDefaultEntity({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, {true, {1, 1}, 0, {255, 255, 255, 255}, (TextData) {"You lose !", FONT_PATH, 100}}, LayerType::FOREGROUND);
    }
    while (refresh() == std::nullopt);
}
