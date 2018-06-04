//
// Created by lucas on 02/06/2018.
//

#include <iostream>
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

Entity World::createEntity()
{
    return (Entity(this, _entityManager.getNextInstance()));
}

void World::info()
{
    std::cout << "\n\n######## Displaying info for World ########\n" << std::endl;
    for (const auto &entity : _entityManager.getEntities()) {
        std::cout << "Entity " << entity << " ------------------- " << std::endl;
        _componentManager.infoComponent(entity);
    }
    std::cout << "\n###########################################" << std::endl;
}