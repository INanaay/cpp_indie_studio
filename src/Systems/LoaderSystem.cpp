//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include "World.hpp"
#include "Components.hpp"
#include "LoaderSystem.hpp"

void Systems::LoaderSystem::execute(World *ref)
{
	while (_engine->isRunning()) {
		auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY});

		for (const auto &entityID : entities) {
			auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(entityID,
													    GRAPHICALBODY);
			auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entityID,
													  PHYSICALBODY);

			if (!graphical->isLoaded) {
				irr::scene::IAnimatedMesh *mesh = _engine->getScene()->getMesh(
					graphical->pathToModel.c_str());
				graphical->node = _engine->getScene()->addAnimatedMeshSceneNode(mesh);
				graphical->isLoaded = true;
			}
			graphical->node->setPosition(irr::core::vector3df(physical->x, physical->y, physical->z));
			graphical->node->setAnimationSpeed(60);

		}
	}
}
