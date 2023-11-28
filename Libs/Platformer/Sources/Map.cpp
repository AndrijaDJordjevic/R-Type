/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Map::Map()
{
    _loadMap = false;
    _nbrMap = 0;

    _pathmap.push_back("Libs/Platformer/Assets/Map/maplvl1.txt");
    _pathmap.push_back("Libs/Platformer/Assets/Map/maplvl3.txt");
    _pathmap.push_back("Libs/Platformer/Assets/Map/maplvl2.txt");
}

Map::~Map()
{
}

void Map::OpenFileMap(std::string path)
{
    std::ifstream map(path);

    if (!map.is_open()) {
         std::cout << "Can't open the file." << std::endl;
    } else {
        std::string ligne;
        while (std::getline(map, ligne))
            _map.push_back(ligne);
        map.close();
    }
    _loadMap = true;
}

void Map::CreateShape(Registry &r, RectangleInfo i)
{
    size_t entity = r.spawnEntity();
    r.emplaceComponent<Position>(entity, i.x, i.y);
    r.emplaceComponent<RectangleShape>(entity, i.width, i.height);
    r.emplaceComponent<Collider>(entity, i.width, i.height);
    r.emplaceComponent<Color>(entity, RED);
    r.emplaceComponent<Velocity>(entity, 0, 0);
    r.emplaceComponent<Clock>(entity, 0.001);
    _entity.push_back(entity);
}

void Map::FindAllShape(Registry &r)
{
    int currentX = 0;
    int currentY = 0;
    int currentWidth = 0;
    int row = 0;
    int tileSizeX = 100;
    int tileSizeY = 50;
    std::vector<RectangleInfo> cubes;

    for (const std::string& line : _map) {
        currentX = 0;
        currentWidth = 0;
        for (int col = 0; col < line.length(); ++col) {
            if (line[col] == 'X') {
                if (currentWidth == 0) {
                    currentX = (col * tileSizeX);
                    currentY = (row * tileSizeY);
                    currentWidth = tileSizeX;
                } else {
                    currentWidth += tileSizeX;
                }
            } else if (currentWidth > 0) {
                RectangleInfo cube;
                cube.x = currentX;
                cube.y = currentY;
                cube.width = currentWidth;
                cube.height = tileSizeY;
                cubes.push_back(cube);
                currentWidth = 0;
            }
        }
        if (currentWidth > 0) {
            RectangleInfo cube;
            cube.x = currentX;
            cube.y = currentY;
            cube.width = currentWidth;
            cube.height = tileSizeY;
            cubes.push_back(cube);
        }
        ++row;
    }

    for (const RectangleInfo& cube : cubes) {
        CreateShape(r, cube);
    }
}

void Map::ClearMap(Registry &r)
{
    for (size_t entity : _entity) {
        r.killEntity(entity);
        _loadMap = false;
    }
}

void Map::Systems(Registry &r)
{
    if (!_loadMap) {
        OpenFileMap(_pathmap[_nbrMap]);
        _nbrMap++;
        FindAllShape(r);
    }
}

void Map::Display(Registry &r, sf::RenderWindow &window)
{
    for (size_t entity : _entity) {
        _rectangle.setPosition(sf::Vector2f(r.getComponents<Position>()[entity]._x, r.getComponents<Position>()[entity]._y));
        _rectangle.setSize(sf::Vector2f(r.getComponents<RectangleShape>()[entity]._width, r.getComponents<RectangleShape>()[entity]._height));
        _rectangle.setFillColor(sf::Color::Red);
        window.draw(_rectangle);
    }
}

void Map::Event(Registry &r, sf::Event &event, sf::RenderWindow &rw)
{
    r.Exec(_ResetMove);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        r.Exec(_MoveX);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        r.Exec(_MoveMX);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        ClearMap(r);
    }
}