//
// Created by lucas on 07/06/2018.
//

#include <iostream>
#include <mutex>
#include <ITexture.h>
#include "World.hpp"
#include "Components.hpp"
#include "ControllableSystem.hpp"

void Systems::ControllableSystem::enableAction(CONTROL_ACTION action, Components::PhysicalBody *physical, Components::Velocity *velocity)
{
    switch (action) {
        case MOVEUP:
            physical->direction = Components::PhysicalBody::Direction::UP;
            velocity->value = 10.f;
            _lastAction = MOVEUP;
            break;
        case MOVEDOWN:
            physical->direction = Components::PhysicalBody::Direction::DOWN;
            velocity->value = 10.f;
            _lastAction = MOVEDOWN;
            break;
        case MOVERIGHT:
            physical->direction = Components::PhysicalBody::Direction::RIGHT;
            velocity->value = 10.f;
            _lastAction = MOVERIGHT;
            break;
        case MOVELEFT:
            physical->direction = Components::PhysicalBody::Direction::LEFT;
            velocity->value = 10.f;
            _lastAction = MOVELEFT;
            break;
    }
}

void Systems::ControllableSystem::disableAction(CONTROL_ACTION action, Components::PhysicalBody *physical, Components::Velocity *velocity)
{
    if (action == _lastAction && action == MOVEUP)
        velocity->value = 0.f;
    if (action == _lastAction && action == MOVEDOWN)
        velocity->value = 0.f;
    if (action == _lastAction && action == MOVERIGHT)
        velocity->value = 0.f;
    if (action == _lastAction && action == MOVELEFT)
        velocity->value = 0.f;
}

void Systems::ControllableSystem::execute(World *ref)
{
    _lastAction = NONE;
    while (_engine->isRunning()) {
        auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, CONTROLLABLE, VELOCITY});

        for (const auto &entityID : entities) {
            auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entityID, PHYSICALBODY);
            auto velocity = ref->getComponentManager().getComponent<Components::Velocity>(entityID, VELOCITY);
            auto controllable = ref->getComponentManager().getComponent<Components::Controllable>(entityID, CONTROLLABLE);

            for (const auto &key : controllable->_keymap) {
                if (_keyDown[key.first])
                    enableAction(key.second, physical, velocity);
                if (!_keyDown[key.first])
                    disableAction(key.second, physical, velocity);
            }
        }
    }
}
