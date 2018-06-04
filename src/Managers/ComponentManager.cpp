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
    std::cout << "Components list for Entity " << id << std::endl;
    for (auto &component : _entities[id]) {
        component->summarize();
    }
}