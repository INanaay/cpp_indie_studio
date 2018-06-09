//
// Created by lucas on 07/06/2018.
//

#include <iostream>
#include <mutex>
#include <ITexture.h>
#include "Components.hpp"
#include "ControllableSystem.hpp"
#include "Bomb.hpp"
#include "Entity.hpp"

void Systems::ControllableSystem::enableAction(World *ref, CONTROL_ACTION action, Components::PhysicalBody *physical, Components::Velocity *velocity, uint32_t id)
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
        case DROP:
            if (physical->dropBomb()) {
                std::cout << "bomb away" << std::endl;
                auto entity = ref->createEntity();
                ref->addEntity(entity);
                entity.addComponent<Components::Bomb>("../ressources/models/cobblestone.obj", "../ressources/models/cobblestone.png", id, 3.0);
            }
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
        auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, CONTROLLABLE, VELOCITY});

        for (const auto &entityID : entities) {
            auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entityID, PHYSICALBODY);
            auto velocity = ref->getComponentManager().getComponent<Components::Velocity>(entityID, VELOCITY);
            auto controllable = ref->getComponentManager().getComponent<Components::Controllable>(entityID, CONTROLLABLE);

            for (const auto &key : controllable->_keymap) {
                if (_keyDown[key.first]) {
                    enableAction(ref, key.second, physical, velocity, entityID);
                }
                if (!_keyDown[key.first])
                    disableAction(key.second, physical, velocity);
            }
        }
}
