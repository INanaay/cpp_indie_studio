//
// Created by lucas on 02/06/2018.
//

#include <iostream>
#include <thread>
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
        std::cout << "\nEntity " << entity << " ------------------- " << std::endl;
        _componentManager.infoComponent(entity);
    }
    std::cout << "\n###########################################" << std::endl;
}

int World::startWorkers()
{
    for (auto &system : _systems) {
        _workers.emplace_back(&ISystem::execute, system, this);
    }
    return 0;
}

int World::waitWorkers()
{
    for (auto &worker : _workers) {
        if (worker.joinable())
            worker.join();
    }
    return 0;
}