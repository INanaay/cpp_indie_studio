//
// Created by clementbmn on 04/06/2018.
//

#include <iostream>
#include "World.hpp"
#include "Components.hpp"
#include "AISystem.hpp"

void Systems::AISystem::execute(World *ref)
{
        auto ai_players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, AI});
        auto blocks = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY});
        auto top_free = true;
        auto right_free = true;
        for (const auto &p : ai_players) {
            auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(p, PHYSICALBODY);
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
            if (top_free)
                physical->y += 0.001f;
            if (right_free)
                physical->x += 0.001f;
        }
}
