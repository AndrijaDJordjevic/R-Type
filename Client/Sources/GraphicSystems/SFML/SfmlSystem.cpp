/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SfmlSystem
*/

#include "SfmlSystem.hpp"

SfmlSystem::SfmlSystem(std::shared_ptr<Clock> clock)
{
    _clock = clock;
    _shape = sf::ConvexShape(4);
    _text = Text("[Default text]", FONT_PATH, sf::Vector2f(100, 100), 50, TOPLEFT);
    _windowSize = sf::Vector2i(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(_windowSize.x, _windowSize.y), "R-Type");

    _spritesData[PLAYER] = (SpriteData) {PLAYER_PATH, std::make_pair(PLAYER_SHEET_WIDTH * PLAYER_SIZE_X, PLAYER_SHEET_HEIGHT * PLAYER_SIZE_Y), {0, 0}, std::make_pair(PLAYER_SIZE_X, PLAYER_SIZE_Y)};
    _spritesData[PROJECTILE] = (SpriteData) {PROJECTILE_PATH, std::make_pair(PROJECTILE_SHEET_WIDTH * PROJECTILE_SIZE_X, PROJECTILE_SHEET_HEIGHT * PROJECTILE_SIZE_Y), {0, 0}, std::make_pair(PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y)};
    _spritesData[ENEMY] = (SpriteData) {ENEMY_PATH, std::make_pair(ENEMY_SHEET_WIDTH * ENEMY_SIZE_X, ENEMY_SHEET_HEIGHT * ENEMY_SIZE_Y), {0, 0}, std::make_pair(ENEMY_SIZE_X, ENEMY_SIZE_Y)};
    _spritesData[CAVE_0] = (SpriteData) {CAVE_0_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
    _spritesData[CAVE_1] = (SpriteData) {CAVE_1_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
    _spritesData[CAVE_2] = (SpriteData) {CAVE_2_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
    _spritesData[CAVE_3] = (SpriteData) {CAVE_3_PATH, std::make_pair(CAVE_SHEET_WIDTH * CAVE_SIZE_X, CAVE_SHEET_HEIGHT * CAVE_SIZE_Y), {0, 0}, std::make_pair(CAVE_SIZE_X, CAVE_SIZE_Y)};
    initSpritePalette();
}

void SfmlSystem::initSprite(std::string path, sf::Vector2i rectDim)
{
    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(path, rectDim);
    if (sprite->isLoaded() == true)
        _spritePalette[path] = sprite;
}

void SfmlSystem::initSpritePalette()
{
    for (auto &spriteData : _spritesData)
        initSprite(spriteData.second.path, sf::Vector2i(spriteData.second.rectDim.first, spriteData.second.rectDim.second));
}

std::unordered_map<int, SpriteData> SfmlSystem::getSpritesProperties()
{
    return _spritesData;
}

void SfmlSystem::draw(Position &pos, Drawable &drawable)
{
    if (drawable.isVisible == false) return;

    if (std::holds_alternative<SpriteData>(drawable.data)) { // if drawable is a Sprite
        SpriteData &data = std::get<SpriteData>(drawable.data);
        if (_spritePalette.find(data.path) == _spritePalette.end()) return; // if sprite not known
        std::shared_ptr<Sprite> sprite = _spritePalette[data.path];
        sprite->setPosition(pos.x, pos.y);
        sprite->moveRectH(data.rectPos.first);
        sprite->moveRectV(data.rectPos.second);
        if (drawable.rotation != 0)
            sprite->setRotation(drawable.rotation);
        if (drawable.scale.first != 1 && drawable.scale.second != 1)
            sprite->setScale(drawable.scale.first, drawable.scale.second);
        if (drawable.color.a != 255)
            sprite->setColor(sf::Color(drawable.color.r, drawable.color.g, drawable.color.b, drawable.color.a));
        _window->draw(*sprite);
    } else if (std::holds_alternative<ShapeData>(drawable.data)) { // if drawable is a Shape
        ShapeData &data = std::get<ShapeData>(drawable.data);
        _shape.setPointCount(data.points.size());
        for (int i = 0; i < (int) data.points.size(); i++)
            _shape.setPoint(i, sf::Vector2f(data.points[i].first, data.points[i].second));
        _shape.setRotation(drawable.rotation);
        _shape.setScale(drawable.scale.first, drawable.scale.second);
        _shape.setFillColor(sf::Color(drawable.color.r, drawable.color.g, drawable.color.b, drawable.color.a));
        _window->draw(_shape);
    } else if (std::holds_alternative<TextData>(drawable.data)) { // if drawable is a Text
        TextData &data = std::get<TextData>(drawable.data);
        _text.setString(data.text);
        if (_text.getFontPath() != data.fontPath)
            _text.setFontFromPath(data.fontPath);
        _text.setCharacterSize(data.fontSize);
        _text.setPosition(pos.x, pos.y);
        _text.setRotation(drawable.rotation);
        _text.setScale(drawable.scale.first, drawable.scale.second);
        _text.setFillColor(sf::Color(drawable.color.r, drawable.color.g, drawable.color.b, drawable.color.a));
        _window->draw(_text);
    }
}

void SfmlSystem::clear()
{
    _window->clear(sf::Color::Black);
}

void SfmlSystem::display()
{
    _window->display();
}

void SfmlSystem::detectKeys(KeysPressed &keysPressed)
{
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window->close();
            keysPressed.windowClosed = true;
            return;
        }
        if (event.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key key = event.key.code;
            KeysCode keyCode = static_cast<KeysCode>(key);
            if (keyCode >= KeysCode::A && keyCode < KeysCode::KeyCount) {
                keysPressed.data[keyCode] = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            sf::Keyboard::Key key = event.key.code;
            KeysCode keyCode = static_cast<KeysCode>(key);
            if (keyCode >= KeysCode::A && keyCode < KeysCode::KeyCount) {
                keysPressed.data[keyCode] = false;
            }
        }
    }
}
