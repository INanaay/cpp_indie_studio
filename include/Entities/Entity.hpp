//
// Created by lucas on 02/06/2018.
//

#ifndef INDIESTUDIO_IENTITY_HPP
#define INDIESTUDIO_IENTITY_HPP

#include <iostream>
#include "Logger.hpp"
#include "World.hpp"

class World;

class Entity {

private:
    World *_world;

public:
    Entity(World *ref, uint32_t idt) : id(idt), _world(ref) {Logger::logMessage("New entity " + std::to_string(id), SUCCESS);};
    ~Entity() noexcept = default;

    template <class componentType, class... Args>
    void addComponent(Args&&... args)
    {
	    _world->getComponentManager().addComponent(new componentType(args...), id);
    };

    template <class componentType>
    void addComponent()
    {
        _world->getComponentManager().addComponent(new componentType(), id);
    };

    void removeComponent(typeComponent rm) {_world->getComponentManager().removeComponent(id, rm);};

public:
    uint32_t id;
};

#endif //INDIESTUDIO_IENTITY_HPP
