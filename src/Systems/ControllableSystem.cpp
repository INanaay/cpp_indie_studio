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

void Systems::ControllableSystem::enableAction(World *ref, CONTROL_ACTION action, Components::PhysicalBody *physical, Components::Velocity *velocity, Components::BombManager *bombManager, uint32_t id)
{
    switch (action) {
        case MOVEUP:
            physical->direction = Components::PhysicalBody::Direction::UP;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            _lastAction = MOVEUP;
            break;
        case MOVEDOWN:
            physical->direction = Components::PhysicalBody::Direction::DOWN;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            _lastAction = MOVEDOWN;
            break;
        case MOVERIGHT:
            physical->direction = Components::PhysicalBody::Direction::RIGHT;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            _lastAction = MOVERIGHT;
            break;
        case MOVELEFT:
            physical->direction = Components::PhysicalBody::Direction::LEFT;
            velocity->old_value = velocity->value;
            velocity->value = 10.f;
            _lastAction = MOVELEFT;
            break;
        case DROP:
            bombManager->putBomb = true;
            _lastAction = DROP;
            break;
    }
}

void Systems::ControllableSystem::disableAction(CONTROL_ACTION action, Components::PhysicalBody *physical, Components::Velocity *velocity, Components::BombManager *bombManager)
{
    if (action == _lastAction && action == MOVEUP)
        velocity->value = 0.f;
    if (action == _lastAction && action == MOVEDOWN)
        velocity->value = 0.f;
    if (action == _lastAction && action == MOVERIGHT)
        velocity->value = 0.f;
    if (action == _lastAction && action == MOVELEFT)
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
                    enableAction(ref, key.second, physical, velocity, bombManager, entityID);
                }
                if (!_keyDown[key.first])
                    disableAction(key.second, physical, velocity, bombManager);
            }
        }
}
