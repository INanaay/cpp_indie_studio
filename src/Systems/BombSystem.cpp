//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include "World.hpp"
#include "Components.hpp"
#include "Bomb.hpp"
#include "BombSystem.hpp"

void Systems::BombSystem::execute(World *ref)
{
	while (_engine->isRunning()) {
		auto entities = ref->getComponentManager().getEntityByComponents({BOMB});
		std::clock_t c_time = std::clock();
		for (const auto &entityID : entities) {
			auto graphical = ref->getComponentManager().getComponent<Components::Bomb>(entityID, BOMB);
			if (!graphical->isLoaded) {
				std::cout << "Loading UI" << std::endl;
				irr::scene::IAnimatedMesh *mesh = _engine->getScene()->getMesh(
					graphical->pathToModel.c_str());
				graphical->node = _engine->getScene()->addAnimatedMeshSceneNode(mesh);
				graphical->isLoaded = true;
			}
			auto explode = graphical->explode(c_time);
		}
	}
}
