/*
** EPITECH PROJECT, 2023
** GameEngine [WSL: Ubuntu]
** File description:
** Registry
*/

#include "Registry.hpp"
#include <stdexcept>
#include <iostream>

Registry::Registry()
{
    _registry = this;
}

Registry &Registry::getCurrentRegitry()
{
    return *_registry;
}

size_t &Registry::spawnEntity()
{
    if (_freeIndexes.size() > 0) {
        size_t index = _freeIndexes.back();
        _freeIndexes.pop_back();
        entities.emplace(entities.end(), index);
    } else
        entities.emplace(entities.end(), _nextEntityId++);
    std::cout << "Spawned entity " << entities.back() << std::endl;
    return entities.back();
}

void Registry::killEntity(size_t const& e)
{
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i] == e) {
            entities.erase(entities.begin() + i);
            _freeIndexes.emplace_back(e);
            return;
        }
    }
}