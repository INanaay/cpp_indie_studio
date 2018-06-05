//
// Created by lucas on 02/06/2018.
//

#ifndef INDIESTUDIO_WORLD_H
#define INDIESTUDIO_WORLD_H

#include <unordered_map>
#include <thread>
#include "ISystem.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"

using SystemsList = std::vector<std::shared_ptr<ISystem>>;
using Workers = std::vector<std::thread>;

/*!
 * \brief This class represent the whole world of the game
 *
 */

class World {

public:
    World();
    ~World() noexcept;

    int update();
    int startWorkers();
    int waitWorkers();

    ComponentManager &getComponentManager() {return _componentManager;};
    EntityManager &getEntityManager() {return _entityManager;};
    Entity createEntity();
    void info();


    template <class systemType, class... Args>
    void addSystem(Args&&... args)
    {
        _systems.emplace_back(new systemType({args...}));
    }

    template <class systemType>
    void addSystem()
    {
        _systems.emplace_back(new systemType());
    }

    void addEntity(Entity &ref)
    {
        _entityManager.addEntity(ref);
    }

private:
    ComponentManager _componentManager;
    EntityManager _entityManager;
    SystemsList _systems;
    Workers _workers;
};


#endif //INDIESTUDIO_WORLD_H
