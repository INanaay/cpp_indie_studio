//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include "World.hpp"
#include "Components.hpp"
#include "BombSystem.hpp"
#include "PhysicalBody.hpp"

void Systems::BombSystem::execute(World *ref)
{
	std::cout << "bomb system executed" << std::endl;
	while (_engine->isRunning()) {
		auto entities = ref->getComponentManager().getEntityByComponents({BOMB});
		std::chrono::time_point<std::chrono::system_clock> c_time = std::chrono::system_clock::now();
		for (auto &entityID : entities) {
			auto graphical = ref->getComponentManager().getComponent<Components::Bomb>(entityID, BOMB);
			auto player = ref->getComponentManager().getComponent<Components::PhysicalBody>(graphical->player_id, PHYSICALBODY);
			if (!graphical->isLoaded) {
				std::cout << "Loading UI" << std::endl;
				irr::scene::IAnimatedMesh *mesh = _engine->getScene()->getMesh(graphical->pathToModel.c_str());
				graphical->node = _engine->getScene()->addAnimatedMeshSceneNode(mesh);
				graphical->setPos(player->x, player->y, player->z);
				graphical->node->setPosition(irr::core::vector3df(player->x, player->y, player->z));
				graphical->isLoaded = true;
			}
			auto explode = graphical->explode(c_time);
			if (explode)
				explodeBomb(ref, graphical, entityID, player);
		}
	}
}

void Systems::BombSystem::explodeBomb(World *ref, Components::Bomb *&bomb, const uint32_t bomb_id, Components::PhysicalBody *&player)
{
	auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY});
	bool playerDestroyed = false;
	for (const auto &entityID : entities) {
		auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entityID, PHYSICALBODY);
		auto x = physical->x - bomb->x;
		auto y = physical->y - bomb->y;
		auto z = physical->z - bomb->z;
		if (x <= bomb->radius && x >= -bomb->radius && y <= bomb->radius && y >= -bomb->radius && z <= bomb->radius && z >= -bomb->radius) {
			std::cout << "destroying item: " << entityID << std::endl;
			auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(entityID, GRAPHICALBODY);
			graphical->node->setVisible(false);
			//_engine->getScene()->addToDeletionQueue(graphical->node);
			if (entityID == bomb->player_id) {
				player->has_dropped = false;
				playerDestroyed = true;
			}
			//ref->getComponentManager().removeComponent(entityID, PHYSICALBODY);
			//ref->getComponentManager().removeComponent(entityID, GRAPHICALBODY);
		}
	}
	_engine->getScene()->addToDeletionQueue(bomb->node);
	ref->getComponentManager().removeComponent(bomb_id, BOMB);
	std::cout << "removed bomb" << std::endl;
	if (!playerDestroyed)
		player->has_dropped = false;
	std::cout << "destroy done" << std::endl;
}