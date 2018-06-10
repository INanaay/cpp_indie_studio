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

void Systems::BombSystem::execute(World *ref) {
    auto bombs = ref->getComponentManager().getEntityByComponents({TIMER, PHYSICALBODY});
    for (auto const &bomb : bombs) {
        auto timer = ref->getComponentManager().getComponent<Components::Timer>(bomb, TIMER);
        auto bombGraphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(bomb, GRAPHICALBODY);
        auto bombPhysical = ref->getComponentManager().getComponent<Components::PhysicalBody>(bomb, PHYSICALBODY);
        auto c_time = std::chrono::system_clock::now();
        if ((c_time - timer->_start).count() >= (3.f * 1000000000.f) &&
            (c_time - timer->_start).count() < (3.5f * 1000000000.f)) {
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
                if (isInRange(bombPhysical->x, bombPhysical->y, physical->x, physical->y)) {
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
                    if (graphical->node->isVisible())
                        graphical->node->setVisible(false);
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
        if (((c_time - timer->_start).count() >= (3.5f * 1000000000.f)) &&
            (c_time - timer->_start).count() <= (4.5f * 1000000000.f)) {
            if (bombGraphical->node->isVisible())
                bombGraphical->node->setVisible(false);
        }
    }
    auto players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, BOMBMANAGER});
    for (auto const &p : players) {
        auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(p, BOMBMANAGER);
        if (bombManager->putBomb) {
            auto player = ref->getComponentManager().getComponent<Components::PhysicalBody>(p, PHYSICALBODY);
            auto bomb = ref->createEntity();
            ref->addEntity(bomb);
            bomb.addComponent<Components::Timer>();
            bomb.addComponent<Components::GraphicalBody>("../ressources/models/tnt.obj",
                                                         "../ressources/models/terrain.png");
            auto div = (player->x + 1.0f) / 2.0f;
            auto round = (float) ((int) div) - 0.5f;
            auto new_x = round * 2.0f;
            div = (player->y + 1.0f) / 2.0f;
            round = (float) ((int) div) - 0.5f;
            auto new_y = (float) round * 2.0f;
            bomb.addComponent<Components::PhysicalBody>(new_x, new_y, 0.0f, false);
        }

    }
}
