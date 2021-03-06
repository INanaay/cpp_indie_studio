//
// Created by lucas on 03/06/2018.
//

#include <iostream>
#include "ComponentManager.hpp"


void ComponentManager::addComponent(IComponent *toPush, uint32_t id)
{
    _entities[id].emplace_back(toPush);
}

void ComponentManager::infoComponent(uint32_t id)
{
    if (_entities.find(id) == _entities.end() && !_entities.empty())
        throw std::runtime_error("Cannot find entity ID");
    for (const auto &entity : _entities[id]) {
        entity->summarize();
    }
}

ComponentsList &ComponentManager::getComponents(uint32_t id)
{
    if (_entities.find(id) == _entities.end())
        throw std::runtime_error("Cannot find entity ID");
    return _entities[id];
}

/*
 * Complexity = O(n²)
*/

std::vector<uint32_t> ComponentManager::getEntityByComponents(std::vector<typeComponent> searchList) const
{
    std::vector<uint32_t> output;

    for (const auto &entity : _entities) {
        int foundCount = 0;
        for (const auto &component : entity.second) {
            for (const auto &search : searchList) {
                if (component->getType() == search)
                    foundCount++;
            }
        }
        if (foundCount == searchList.size())
            output.push_back(entity.first);
    }
    return output;
}

void ComponentManager::removeComponent(uint32_t id, typeComponent rm)
{
    if (_entities.find(id) == _entities.end())
        throw std::runtime_error("Cannot find entity for this ID");
    for (auto it = _entities[id].begin(); it != _entities[id].end(); it++) {
        if ((*it)->getType() == rm) {
            _entities[id].erase(it);
            return;
        }
    }
}

void ComponentManager::removeComponents()
{
    for (auto &entity : _entities) {
        entity.second.clear();
    }
}