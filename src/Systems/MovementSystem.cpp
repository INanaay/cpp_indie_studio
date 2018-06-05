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

std::mutex positionComponentMutex;

void Systems::MovementSystem::execute(World *ref)
{
	//irr::u32 then = _engine->getDevice()->getTimer()->getRealTime();
	while (_engine->isRunning()) {
		auto entities = ref->getComponentManager().getEntityByComponents(
			{PHYSICALBODY, VELOCITY});

		for (const auto &entityID : entities) {

			auto velocity = ref->getComponentManager().getComponent<Components::Velocity>(
				entityID,
				VELOCITY);
			auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(
				entityID,
				PHYSICALBODY);
			/* const irr::u32 now = _engine->getDevice()->getTimer()->getTime();
			const irr::f32 frameDeltaTime =
				(irr::f32) (now - then) /
				1000.f; // Time in seconds
			then = now; */
			positionComponentMutex.lock();

			if (physical->direction ==
			    Components::PhysicalBody::Direction::LEFT)
				physical->x = physical->x - velocity->value;
			else if (physical->direction ==
				 Components::PhysicalBody::Direction::RIGHT)
				physical->x = physical->x +
					      velocity->value;
			else if (physical->direction ==
				 Components::PhysicalBody::Direction::UP)
				physical->y = physical->y +
					      velocity->value;
			else
				physical->y = physical->y -
					      velocity->value;
			positionComponentMutex.unlock();
		}
	}
}
