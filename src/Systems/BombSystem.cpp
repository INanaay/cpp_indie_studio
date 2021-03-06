//
// Created by lucas on 04/06/2018.
//

#include <iostream>
#include <algorithm>
#include "Entity.hpp"
#include "World.hpp"
#include "Components.hpp"
#include "BombSystem.hpp"
#include "PhysicalBody.hpp"
#include <cmath>
#include <Pickup.hpp>

#define CONVERT_TIME 1000000000

bool isInRange(float x, float y, float x2, float y2)
{
    if (x == x2 && y == y2) {
        return true;
    } else if (x == x2) {
        if (fabs(y2 - y) <= 2.0f) {
            return true;
        }
    } else if (y == y2) {
        if (fabs(x2 - x) <= 2.0f) {
            return true;
        }
    } else {
        return false;
    }
}

void Systems::BombSystem::putPickup(Components::GraphicalBody *wall, World *ref)
{
	int randNum = rand()%(100) + 1;

	if (randNum <= 90)
	{
		int randType = rand()%(3) + 1;

		auto pos = wall->node->getPosition();
		auto bomb = ref->createEntity();
		ref->addEntity(bomb);

		bomb.addComponent<Components::PhysicalBody>(pos.X, pos.Y, 0.0f, false);
		switch (randType) {
			case 1 :
				bomb.addComponent<Components::Pickup>(SPEEDPICKUP);
				bomb.addComponent<Components::GraphicalBody>("ressources/models/pickup0.obj",
									     "ressources/models/terrain.png");
				break;
			case 2:
				bomb.addComponent<Components::Pickup>(RADIUSPICKUP);
				bomb.addComponent<Components::GraphicalBody>("ressources/models/pickup1.obj",
									     "ressources/models/terrain.png");
				break;
			case 3:
				bomb.addComponent<Components::Pickup>(BOMBPICKUP);
				bomb.addComponent<Components::GraphicalBody>("ressources/models/pickup2.obj",
									     "ressources/models/terrain.png");
				break;
			default : break;
		}
	}

}

void Systems::BombSystem::updateBombs(World *ref) {
    auto c_time = std::chrono::high_resolution_clock::now();
    auto players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, BOMBMANAGER});
    for (auto const &p : players) {
        auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(p, BOMBMANAGER);
        auto &bombs = bombManager->bombs;
        for (const auto &bomb : bombs) {
            auto timer = ref->getComponentManager().getComponent<Components::Timer>(bomb, TIMER);
            if (((c_time - timer->_start).count() >= (3.2f * CONVERT_TIME))) {
                auto it = std::find(bombs.begin(), bombs.end(), bomb);
                if (it != bombs.end()) {
                    bombs.erase(it);
                }
            }
        }
    }
}

void putNewBombs(World *ref) {
    auto players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, BOMBMANAGER});
    for (auto const &p : players) {
        auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(p, BOMBMANAGER);
        if (bombManager->putBomb && (bombManager->bombs.size() < bombManager->availables) == true) {
            auto player = ref->getComponentManager().getComponent<Components::GraphicalBody>(p, GRAPHICALBODY)->node->getPosition();
            auto div = player.X / 2.0f;
            auto round = (int)(truncf(div));
            float new_x;
            new_x = (float)round * 2.0f + (player.X < 0.f ? -1.0f : 1.0f);
            div = player.Y / 2.0f;
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
            auto bombs = ref->getComponentManager().getEntityByComponents({TIMER, GRAPHICALBODY});
            for (const auto &bomb : bombs) {
                auto node = ref->getComponentManager().getComponent<Components::GraphicalBody>(bomb, GRAPHICALBODY)->node;
                if (node != nullptr) {
                    auto pos = node->getPosition();
                    if (node->isVisible() && pos.X == new_x && pos.Y == new_y) {
                        canPut = false;
                        break;
                    }
                }
            }
            if (canPut) {
                auto bomb = ref->createEntity();
                bombManager->bombs.push_back(bomb.id);
                ref->addEntity(bomb);
                bomb.addComponent<Components::Timer>();
                bomb.addComponent<Components::GraphicalBody>("ressources/models/tnt.obj",
                                                             "ressources/models/terrain.png");
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
    bombGraphical->mesh = _engine->getScene()->getMesh("ressources/models/explosion.obj");
    bombGraphical->node = _engine->getScene()->addAnimatedMeshSceneNode(bombGraphical->mesh);
    bombGraphical->node->setMaterialTexture(0, _engine->getDriver()->getTexture(
            "ressources/models/terrain.png"));
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
            otherTimer->_start = timer->_start + std::chrono::milliseconds(50);
        }
    }
    auto entities = ref->getComponentManager().getEntityByComponents(
            {PHYSICALBODY, GRAPHICALBODY, WALLCOLLISION});
    for (const auto &entity : entities) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(
                entity, PHYSICALBODY);
        auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
                entity, GRAPHICALBODY);
        auto pos = graphical->node->getPosition();
        if ((physical->_destroyable) && (isInRange(bombPhysical->x, bombPhysical->y, pos.X, pos.Y) == true)) {
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
	    auto div = physical->x / 2.0f;
	    auto round = (int)(truncf(div));
	    float new_x;
	    new_x = (float)round * 2.0f + (physical->x < 0.f ? -1.0f : 1.0f);
	    div = physical->y / 2.0f;
	    round = (int)(truncf(div));
	    float new_y;
	    new_y = (float)round * 2.0f + (physical->y < 0.f ? -1.0f : 1.0f);
        if (isInRange(bombPhysical->x, bombPhysical->y, new_x, new_y) == true) {
		auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
                    p, GRAPHICALBODY);
		if (graphical->node->isVisible() == true) {
			ref->getComponentManager().removeComponent(p, BOMBMANAGER);
			ref->getComponentManager().removeComponent(p, CONTROLLABLE);
			graphical->node->setVisible(false);
		}


        }
    }

}

void Systems::BombSystem::execute(World *ref) {
    auto bombs = ref->getComponentManager().getEntityByComponents({TIMER, PHYSICALBODY});
    for (auto const &bomb : bombs) {
        auto bombGraphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(bomb, GRAPHICALBODY);
        if (bombGraphical->node->isVisible() == false)
            continue;
        auto timer = ref->getComponentManager().getComponent<Components::Timer>(bomb, TIMER);
        auto bombPhysical = ref->getComponentManager().getComponent<Components::PhysicalBody>(bomb, PHYSICALBODY);
        auto c_time = std::chrono::high_resolution_clock::now();

        if ((c_time - timer->_start).count() >= (3.f * CONVERT_TIME) &&
            (c_time - timer->_start).count() < (3.5f * CONVERT_TIME)) {
            explodeBomb(ref, bomb, bombGraphical, bombPhysical, timer);
        }
        if (((c_time - timer->_start).count() >= (3.5f * CONVERT_TIME)) &&
            (c_time - timer->_start).count() <= (3.6f * CONVERT_TIME)) {
            if (bombGraphical->node->isVisible())
                bombGraphical->node->setVisible(false);
        }
    }
    updateBombs(ref);
    putNewBombs(ref);
}
