/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/06 by cjdcoy
*/

//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include "World.hpp"
#include "Components.hpp"
#include "MovementSystem.hpp"

void Systems::MovementSystem::execute(World *ref)
{
	/*while (_engine->isRunning()) {
		auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, VELOCITY});

		for (const auto &entityID : entities) {
			auto velocity = ref->getComponentManager().getComponent<Components::GraphicalBody>(entityID,
													    GRAPHICALBODY);
			auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entityID,
													  PHYSICALBODY);

			if (!velocity->isLoaded) {
				irr::scene::IAnimatedMesh *mesh = _engine->getScene()->getMesh(
					velocity->pathToModel.c_str());
				velocity->node = _engine->getScene()->addAnimatedMeshSceneNode(mesh);
				velocity->isLoaded = true;
			}
			velocity->node->setPosition(irr::core::vector3df(physical->x, physical->y, physical->z));
			velocity->node->setAnimationSpeed(60);
		}
	}*/
}
