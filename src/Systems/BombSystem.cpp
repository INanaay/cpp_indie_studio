//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include "Entity.hpp"
#include "World.hpp"
#include "Components.hpp"
#include "BombSystem.hpp"
#include "PhysicalBody.hpp"
#include <cmath>
#include <Pickup.hpp>

bool isInRange(float x, float y, float x2, float y2)
{
    if (x == x2 && y == y2) {
        return false;
    } else if (x == x2) {
        if (fabs(y2 - y) <= 2.0f)
            return true;
    } else if (y == y2) {
        if (fabs(x2 - x) <= 2.0f)
            return true;
    } else {
        return false;
    }
}

void Systems::BombSystem::putPickup(Components::GraphicalBody *wall, World *ref)
{
	int randNum = rand()%(4 -1 + 1) + 1;
	std::cout << "Rand = " << randNum << std::endl;

	if (randNum == 2)
	{
		int randType = rand()%(3 -1 + 1) + 1;

		auto pos = wall->node->getPosition();
		std::cout << "PUT PICKUP\n";
		std::cout << "Type of pickup  = " << randType << std::endl;
		auto bomb = ref->createEntity();
		ref->addEntity(bomb);

		bomb.addComponent<Components::PhysicalBody>(pos.X, pos.Y, 0.0f, false);
		switch (randType) {
			case 1 :
				bomb.addComponent<Components::Pickup>(SPEEDPICKUP);
				bomb.addComponent<Components::GraphicalBody>("../ressources/models/mushroom.obj",
									     "../ressources/models/terrain.png");
				break;
			case 2:
				bomb.addComponent<Components::Pickup>(RADIUSPICKUP);
				bomb.addComponent<Components::GraphicalBody>("../ressources/models/mushroom.obj",
									     "../ressources/models/terrain.png");
				break;
			case 3:
				bomb.addComponent<Components::Pickup>(BOMBPICKUP);
				bomb.addComponent<Components::GraphicalBody>("../ressources/models/mushroom.obj",
									     "../ressources/models/terrain.png");
				break;
			default : break;
		}
	}

}

void putNewBombs(World *ref) {
    auto players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, BOMBMANAGER});
    for (auto const &p : players) {
        auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(p, BOMBMANAGER);
        if (bombManager->putBomb) {
            auto player = ref->getComponentManager().getComponent<Components::GraphicalBody>(p, GRAPHICALBODY)->node->getPosition();
            auto div = (player.X) / 2.0f;
            auto round = (int)(truncf(div));
            float new_x;
            new_x = (float)round * 2.0f + (player.X < 0.f ? -1.0f : 1.0f);
            div = (player.Y) / 2.0f;
            round = (int)(truncf(div));
            float new_y;
            new_y = (float)round * 2.0f + (player.Y < 0.f ? -1.0f : 1.0f);
            auto blocks = ref->getComponentManager().getEntityByComponents({WALLCOLLISION});
            bool canPut = true;
            for (const auto &block : blocks) {
                auto node = ref->getComponentManager().getComponent<Components::GraphicalBody>(block, GRAPHICALBODY)->node;
                auto pos = node->getPosition();
                if (node->isVisible() && pos.X == new_x && pos.Y == new_y) {
                    canPut = false;
                    break;
                }
            }
            if (canPut) {
                auto bomb = ref->createEntity();
                ref->addEntity(bomb);
                bomb.addComponent<Components::Timer>();
                bomb.addComponent<Components::GraphicalBody>("../ressources/models/tnt.obj",
                                                             "../ressources/models/terrain.png");
                bomb.addComponent<Components::PhysicalBody>(new_x, new_y, 0.0f, false);
            }
        }

    }
}

void Systems::BombSystem::explodeBomb(World *ref, const uint32_t &bomb,
                                      Components::GraphicalBody *&bombGraphical,
                                      Components::PhysicalBody *&bombPhysical,
                                      Components::Timer *&timer) {
    if (bombGraphical->node->isVisible())
        bombGraphical->node->setVisible(false);
    bombGraphical->mesh = _engine->getScene()->getMesh("../ressources/models/explosion.obj");
    bombGraphical->node = _engine->getScene()->addAnimatedMeshSceneNode(bombGraphical->mesh);
    bombGraphical->node->setMaterialTexture(0, _engine->getDriver()->getTexture(
            "../ressources/models/terrain.png"));
    bombGraphical->node->setPosition(irr::core::vector3df(bombPhysical->x, bombPhysical->y, 0.0f));
    bombGraphical->node->setRotation(irr::core::vector3df(270, 0, 0));
    auto otherBombs = ref->getComponentManager().getEntityByComponents(
            {TIMER});
    for (const auto &otherBomb : otherBombs) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(
                otherBomb, PHYSICALBODY);
        auto otherTimer = ref->getComponentManager().getComponent<Components::Timer>(
                otherBomb, TIMER);
        if (((otherTimer->_start - timer->_start).count() > 0) && isInRange(bombPhysical->x, bombPhysical->y, physical->x, physical->y)) {
            otherTimer->_start = timer->_start;
        }
    }
    auto entities = ref->getComponentManager().getEntityByComponents(
            {PHYSICALBODY, GRAPHICALBODY, WALLCOLLISION});
    for (const auto &entity : entities) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(
                entity, PHYSICALBODY);
        if (physical->_destroyable && isInRange(bombPhysical->x, bombPhysical->y, physical->x, physical->y)) {
            auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
                    entity, GRAPHICALBODY);
            auto wallcollision = ref->getComponentManager().getComponent<Components::WallCollision>(entity,
                                                                                                    WALLCOLLISION);
            _engine->getMetaSelector()->removeTriangleSelector(wallcollision->selector);
            if (graphical->node->isVisible()) {
		    graphical->node->setVisible(false);
		    putPickup(graphical, ref);
	    }

        }
    }
    auto players = ref->getComponentManager().getEntityByComponents(
            {PHYSICALBODY, GRAPHICALBODY, PLAYERCOLLISION});
    for (auto const &p : players) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(
                p, PHYSICALBODY);
        if (isInRange(bombPhysical->x, bombPhysical->y, physical->x, physical->y)) {
            auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
                    p, GRAPHICALBODY);
            //TODO kill players
        }
    }

}

void Systems::BombSystem::execute(World *ref) {
    auto bombs = ref->getComponentManager().getEntityByComponents({TIMER, PHYSICALBODY});
    for (auto const &bomb : bombs) {

        auto bombGraphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(bomb, GRAPHICALBODY);
        auto timer = ref->getComponentManager().getComponent<Components::Timer>(bomb, TIMER);
        auto bombPhysical = ref->getComponentManager().getComponent<Components::PhysicalBody>(bomb, PHYSICALBODY);
        auto c_time = std::chrono::high_resolution_clock::now();
        if ((c_time - timer->_start).count() >= (3.f * 1000000000.f) &&
            (c_time - timer->_start).count() < (3.5f * 1000000000.f)) {
            explodeBomb(ref, bomb, bombGraphical, bombPhysical, timer);
        }
        if (((c_time - timer->_start).count() >= (3.5f * 1000000000.f)) &&
            (c_time - timer->_start).count() <= (4.5f * 1000000000.f)) {
            if (bombGraphical->node->isVisible())
                bombGraphical->node->setVisible(false);
        }
    }
    putNewBombs(ref);
}
