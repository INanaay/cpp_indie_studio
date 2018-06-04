//
// Created by lucas on 02/06/2018.
//

#include "Logger.hpp"
#include "Entity.hpp"
#include "World.hpp"

World::World()
{
    Logger::logMessage("New world created", SUCCESS);
}

World::~World()
{

}

int World::update()
{
    for (auto &system : _systems) {
        system->execute(this);
    }
    return 0;
}

Entity *World::createEntity()
{
    _entities.emplace_back(new Entity(this, ++_stats.entitiesCount));
    return _entities.back().get();
}