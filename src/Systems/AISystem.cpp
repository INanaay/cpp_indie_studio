//
// Created by clementbmn on 04/06/2018.
//

#include <iostream>
#include "World.hpp"
#include "Components.hpp"
#include "AISystem.hpp"

std::vector<std::vector<unsigned char>> getMap(World *ref) {
    auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY});
    for (const auto &entity : entities) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entity, PHYSICALBODY);
        auto x = (int)physical->x;
        auto y = (int)physical->x;
    }
}

void Systems::AISystem::execute(World *ref)
{
        auto ai_players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, AI});
        auto blocks = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, WALLCOLLISION});
        auto top_free = true;
        auto right_free = true;
        for (const auto &p : ai_players) {
            auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(p, PHYSICALBODY);
            auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(p, GRAPHICALBODY);
            for (const auto &block : blocks) {
                auto pos_x= ref->getComponentManager().getComponent<Components::PhysicalBody>(block, PHYSICALBODY)->x;
                auto pos_y= ref->getComponentManager().getComponent<Components::PhysicalBody>(block, PHYSICALBODY)->y;
                if (physical->y <= pos_y && physical->y + 2.0 >= pos_y) {
                    top_free = false;
                }
                if (physical->x <= pos_x && physical->x + 2.0 >= pos_x) {
                    right_free = false;
                }
            }
            auto pos = graphical->node->getPosition();
            pos.X -= 0.5f;
            pos.Y -= 0.5f;
            graphical->node->setPosition(pos);
        }
}
