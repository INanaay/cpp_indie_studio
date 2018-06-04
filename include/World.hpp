//
// Created by lucas on 02/06/2018.
//

#ifndef INDIESTUDIO_WORLD_H
#define INDIESTUDIO_WORLD_H

#include <unordered_map>
#include "ISystem.hpp"
#include "ComponentManager.hpp"

class Entity;
using Entities = std::vector<std::unique_ptr<Entity>>;
using Systems = std::vector<std::unique_ptr<ISystem>>;

struct WorldStats
{
    WorldStats() : entitiesCount(0), componentsCount(0) {};
    uint32_t entitiesCount;
    uint32_t componentsCount;
};

/*!
 * \brief This class represent the whole world of the game
 *
 */

class World {

public:
    World();
    ~World() noexcept;

    int update();

    ComponentManager *getComponentManager() {return &_componentManager;};
    Entity *createEntity();


    template <class systemType, class... Args>
    void addSystem(Args&&... args)
    {
        _systems.emplace_back(new systemType({args...}));
    }

private:
    ComponentManager _componentManager;
    Entities _entities;
    Systems _systems;
    WorldStats _stats;
};


#endif //INDIESTUDIO_WORLD_H
