/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/06 by cjdcoy
*/

//
// Created by lucas on 04/06/2018.
//

#include <mutex>
#include <iostream>
#include "World.hpp"
#include "Components.hpp"
#include "MovementSystem.hpp"
#include "Entity.hpp"

void Systems::MovementSystem::execute(World *ref)
{
		static irr::u32 then = _engine->getDevice()->getTimer()->getTime();
		auto entities = ref->getComponentManager().getEntityByComponents(
			{PHYSICALBODY, VELOCITY, GRAPHICALBODY, CONTROLLABLE});
		const irr::u32 now = _engine->getDevice()->getTimer()->getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		for (const auto &entityID : entities) {
            auto ctrl = ref->getComponentManager().getComponent<Components::Controllable>(
                    entityID,
                    CONTROLLABLE);
			auto velocity = ref->getComponentManager().getComponent<Components::Velocity>(
				entityID,
				VELOCITY);
			auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(
				entityID,
				PHYSICALBODY);
			auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
					entityID,
					GRAPHICALBODY);
            auto controllable = ref->getComponentManager().getComponent<Components::Controllable>(
                    entityID, CONTROLLABLE);
            if (graphical->isLoaded) {
                auto node = graphical->node;
				auto pos = node->getPosition();

                bool wasKeyPressed = ctrl->isKeyPressed;
                ctrl->isKeyPressed = false;
                for (auto &key : controllable->_keymap) {
                    if (_keyDown[key.first]) {
                        ctrl->isKeyPressed = true;
                        break;
                    }
                }
                if (!ctrl->isKeyPressed) {
                    node->setFrameLoop(34, 34);
                } else {
                    if (!wasKeyPressed) {
                        node->setFrameLoop(1, 35);
                        node->setAnimationSpeed(velocity->baseVelocity * 6);
                    }
                }
                graphical->node->setRotation(irr::core::vector3df(270, 0, physical->direction));
                if (physical->direction == Components::PhysicalBody::Direction::LEFT)
					pos.X -= velocity->value * frameDeltaTime;
				else if (physical->direction == Components::PhysicalBody::Direction::RIGHT)
					pos.X += velocity->value * frameDeltaTime;
				else if (physical->direction == Components::PhysicalBody::Direction::UP)
					pos.Y += velocity->value * frameDeltaTime;
				else if (physical->direction == Components::PhysicalBody::Direction::DOWN)
					pos.Y -= velocity->value * frameDeltaTime;

				node->setPosition(pos);
                if (pos.X == physical->x && pos.Y == physical->y) {
                    velocity->old_value = velocity->value;
                    velocity->value = 0.f;
                }
				if (pos.X != physical->x)
					physical->x = pos.X;
                if (pos.Y != physical->y)
                    physical->y = pos.Y;

            }
		}
}
