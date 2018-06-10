//
// Created by lucas on 04/06/2018.
//

#include <Entity.hpp>
#include <iostream>
#include <algorithm>
#include "EntityManager.hpp"

void EntityManager::addEntity(Entity &entity)
{
    if (std::find(_added.begin(), _added.end(), entity.id) != _added.end())
        throw std::runtime_error("The entity ID already exist");
    _added.push_back(entity.id);
}

uint32_t EntityManager::getNextInstance()
{
    return (++_entityCount);
}

void EntityManager::foreachEntity(std::function<void(uint32_t)> fun) const
{
    for (const auto &e : _added) {
        fun(e);
    }
}

void EntityManager::deleteEntity(uint32_t id)
{
    auto it = std::find(_added.begin(), _added.end(), id);
    if (it != _added.end())
        _added.erase(it);

}