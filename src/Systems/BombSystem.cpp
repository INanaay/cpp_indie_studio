//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include <Entity.hpp>
#include "World.hpp"
#include "Components.hpp"
#include "BombSystem.hpp"
#include "PhysicalBody.hpp"

void Systems::BombSystem::execute(World *ref)
{
	auto players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY ,BOMBMANAGER});
    auto c_time = std::chrono::system_clock::now();
	for (auto const &p : players) {
        auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(p, BOMBMANAGER);
        if (bombManager->putBomb) {
            auto player = ref->getComponentManager().getComponent<Components::PhysicalBody>(p, PHYSICALBODY);
            auto bomb = ref->createEntity();
            ref->addEntity(bomb);
            bomb.addComponent<Components::Timer>();
            bomb.addComponent<Components::GraphicalBody>("../ressources/models/bomb.obj", "../ressources/models/terrain.png");
            auto div = player->x / 1.602f;
            auto round = (int)div;
            auto new_x = (float)round * 1.602f;
            div = player->y / 1.602f;
            round = (int)div - 1;
            auto new_y = (float)round * 1.602f;
            bomb.addComponent<Components::PhysicalBody>(new_x, new_y, 0.0f);
        }

	}
    auto bombs = ref->getComponentManager().getEntityByComponents({TIMER});
	for (auto const &bomb : bombs) {
	    auto timer = ref->getComponentManager().getComponent<Components::Timer>(bomb, TIMER);
	    if ((c_time - timer->_start).count() >= 3 * 1000000000) {
            auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY});
            for (const auto &entity : entities) {
            }
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
            auto wallcollision = ref->getComponentManager().getComponent<Components::WallCollision>(entityID, WALLCOLLISION);
            if (wallcollision != nullptr) {
                ref->getEntityManager().deleteEntity(entityID);
                _engine->getMetaSelector()->removeTriangleSelector(wallcollision->selector);
                _engine->getScene()->addToDeletionQueue(graphical->node);
            }

			if (entityID == bomb->player_id) {
                ref->getEntityManager().deleteEntity(bomb->player_id);
                _engine->getScene()->addToDeletionQueue(graphical->node);
				player->has_dropped = false;
                playerDestroyed = true;
			}
		}
	}
	_engine->getScene()->addToDeletionQueue(bomb->node);
	ref->getComponentManager().removeComponent(bomb_id, BOMB);
	std::cout << "removed bomb" << std::endl;
	if (!playerDestroyed)
		player->has_dropped = false;
	std::cout << "destroy done" << std::endl;
}