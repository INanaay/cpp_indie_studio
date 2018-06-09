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
		static irr::u32 then = _engine->getDevice()->getTimer()->getTime();
		auto entities = ref->getComponentManager().getEntityByComponents(
			{PHYSICALBODY, VELOCITY, GRAPHICALBODY});

		const irr::u32 now = _engine->getDevice()->getTimer()->getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		for (const auto &entityID : entities) {

			auto velocity = ref->getComponentManager().getComponent<Components::Velocity>(
				entityID,
				VELOCITY);
			auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(
				entityID,
				PHYSICALBODY);
			auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
					entityID,
					GRAPHICALBODY);
			if (graphical->isLoaded) {
				auto pos = graphical->node->getPosition();
				if (physical->direction == Components::PhysicalBody::Direction::LEFT)
					pos.X -= velocity->value * frameDeltaTime;
				else if (physical->direction == Components::PhysicalBody::Direction::RIGHT)
					pos.X += velocity->value * frameDeltaTime;
				else if (physical->direction == Components::PhysicalBody::Direction::UP)
					pos.Y += velocity->value * frameDeltaTime;
				else if (physical->direction == Components::PhysicalBody::Direction::DOWN)
					pos.Y -= velocity->value * frameDeltaTime;

				graphical->node->setPosition(pos);
				if (pos != graphical->node->getPosition()) {
					physical->x = pos.X;
					physical->y = pos.Y;
					physical->z = pos.Z;
				}
			}
		}
}
