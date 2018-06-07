//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include <mutex>
#include <ITexture.h>
#include "World.hpp"
#include "Components.hpp"
#include "LoaderSystem.hpp"

extern std::mutex positionComponentMutex;

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
				graphical->mesh = _engine->getScene()->getMesh(
					graphical->pathToModel.c_str());
				graphical->node = _engine->getScene()->addAnimatedMeshSceneNode(graphical->mesh);
				graphical->node->setMaterialTexture(0, _engine->getDriver()->getTexture(graphical->pathToTexture.c_str()));
				graphical->isLoaded = true;
			}
			positionComponentMutex.lock();
			graphical->node->setPosition(irr::core::vector3df(physical->x, physical->y, physical->z));
			positionComponentMutex.unlock();
			graphical->node->setAnimationSpeed(60);
		}
	}
}
