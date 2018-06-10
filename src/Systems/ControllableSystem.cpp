//
// Created by lucas on 07/06/2018.
//

#include <iostream>
#include <mutex>
#include <ITexture.h>
#include "Components.hpp"
#include "ControllableSystem.hpp"
#include "BombManager.hpp"
#include "Entity.hpp"

void Systems::ControllableSystem::enableAction(World *ref, CONTROL_ACTION action, Components::PhysicalBody *physical, Components::Velocity *velocity, Components::BombManager *bombManager, Components::Controllable *controllable, uint32_t id)
{
    switch (action) {
        case MOVEUP:
            physical->direction = Components::PhysicalBody::Direction::UP;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            controllable->_lastAction = MOVEUP;
            break;
        case MOVEDOWN:
            physical->direction = Components::PhysicalBody::Direction::DOWN;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            controllable->_lastAction = MOVEDOWN;
            break;
        case MOVERIGHT:
            physical->direction = Components::PhysicalBody::Direction::RIGHT;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            controllable->_lastAction = MOVERIGHT;
            break;
        case MOVELEFT:
            physical->direction = Components::PhysicalBody::Direction::LEFT;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            controllable->_lastAction = MOVELEFT;
            break;
        case DROP:
            bombManager->putBomb = true;
            controllable->_lastAction = DROP;
            break;
    }
}

void Systems::ControllableSystem::disableAction(CONTROL_ACTION action, Components::PhysicalBody *physical, Components::Velocity *velocity, Components::BombManager *bombManager, Components::Controllable *controllable)
{
    if (action == controllable->_lastAction && action == MOVEUP)
        velocity->value = 0.f;
    if (action == controllable->_lastAction && action == MOVEDOWN)
        velocity->value = 0.f;
    if (action == controllable->_lastAction && action == MOVERIGHT)
        velocity->value = 0.f;
    if (action == controllable->_lastAction && action == MOVELEFT)
        velocity->value = 0.f;
    if (action == DROP)
        bombManager->putBomb = false;
}

void Systems::ControllableSystem::execute(World *ref)
{
    auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, CONTROLLABLE, VELOCITY, BOMBMANAGER});

    for (const auto &entityID : entities) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entityID, PHYSICALBODY);
        auto velocity = ref->getComponentManager().getComponent<Components::Velocity>(entityID, VELOCITY);
        auto controllable = ref->getComponentManager().getComponent<Components::Controllable>(entityID, CONTROLLABLE);
        auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(entityID, BOMBMANAGER);
        for (const auto &key : controllable->_keymap) {
            if (_keyDown[key.first]) {
                enableAction(ref, key.second, physical, velocity, bombManager, controllable, entityID);
            }
            if (!_keyDown[key.first])
                disableAction(key.second, physical, velocity, bombManager, controllable);
        }
    }
    auto ais = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, AI, VELOCITY, BOMBMANAGER});
    for (const auto &ai : ais) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(ai, PHYSICALBODY);
        auto velocity = ref->getComponentManager().getComponent<Components::Velocity>(ai, VELOCITY);
        auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(ai, BOMBMANAGER);
        auto aiComponent = ref->getComponentManager().getComponent<Components::AIComponent>(ai, AI);
        auto controllable = ref->getComponentManager().getComponent<Components::Controllable>(ai, CONTROLLABLE);
        enableAction(ref, aiComponent->action, physical, velocity, bombManager, controllable, ai);
    }
}
