//
// Created by clementbmn on 04/06/2018.
//

#include <iostream>
#include <random>
#include "World.hpp"
#include "Components.hpp"
#include "AISystem.hpp"

void printMap(std::vector<std::vector<unsigned char>> map) {
    std::cout << std::endl;
    for (auto y : map) {
        for (auto x : y) {
            std::cout << x;
        }
        std::cout << std::endl;
    }
}

static bool isInRange(float x, float y, float x2, float y2) {
    if (x == x2 && y == y2) {
        return true;
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

std::vector<std::vector<unsigned char>> Systems::AISystem::getMap(World *ref) {
    for (int x = 0; x < _map.size(); x++) {
        for (int y = 0; y < _map[0].size(); y++) {
            _map[x][y] = '0';
        }
    }
    auto entities = ref->getComponentManager().getEntityByComponents({PHYSICALBODY});
    for (const auto &entity : entities) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(entity, PHYSICALBODY);
        auto div = (physical->x) / 2.0f;
        auto round = (int) (truncf(div));
        float new_x;
        new_x = (float) round * 2.0f + (physical->x < 0.f ? -1.0f : 1.0f);
        div = (physical->y) / 2.0f;
        round = (int) (truncf(div));
        float new_y;
        new_y = (float)round * 2.0f + (physical->y < 0.f ? -1.0f : 1.0f);
        if ((_map[16 - (new_y / 2 + 8)][new_x / 2 + 8] == '0') || (_map[16 - (new_y / 2 + 8)][new_x / 2 + 8] == '3')) {
            if (ref->getComponentManager().getComponent<Components::WallCollision>(entity, WALLCOLLISION) != nullptr) {
                _map[16 - (new_y / 2 + 8)][new_x / 2 + 8] = physical->_destroyable ? '1' : '4';
            } else if (ref->getComponentManager().getComponent<Components::Timer>(entity, TIMER) != nullptr) {
                _map[16 - (new_y / 2 + 8)][new_x / 2 + 8] = '2';
            } else if (ref->getComponentManager().getComponent<Components::PlayerCollision>(entity, PLAYERCOLLISION) != nullptr) {
                _map[16 - (new_y / 2 + 8)][new_x / 2 + 8] = '3';
            }
        }
    }
    return _map;
}

static unsigned long myRand(std::size_t from, std::size_t to)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> toRet(from, to);
    return toRet(rng);
}

uint32_t  getBlock(World *ref, float x, float y) {
    auto blocks = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY});
    for (const auto &block : blocks) {
        auto graph = ref->getComponentManager().getComponent<Components::GraphicalBody>(block, GRAPHICALBODY);
        if (graph->node->isVisible() && (graph->node->getPosition().X == x) && (graph->node->getPosition().Y == y))
            return block;
    }
    auto bombs = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, TIMER});
    for (const auto &bomb : bombs) {
        auto graph = ref->getComponentManager().getComponent<Components::GraphicalBody>(bomb, GRAPHICALBODY);
        if (graph->node->isVisible() && isInRange(graph->node->getPosition().X, graph->node->getPosition().X, x, y))
            return 1;
    }
    return 0;
}

bool goodCell(World *ref, float x, float y) {
    auto blocks = std::vector<uint32_t>();
    blocks.push_back(getBlock(ref, x - 2, y));
    blocks.push_back(getBlock(ref, x + 2, y));
    blocks.push_back(getBlock(ref, x, y - 2));
    blocks.push_back(getBlock(ref, x, y + 2));
    for (const auto &block : blocks) {
        if (block != 0) {
            auto phys = ref->getComponentManager().getComponent<Components::PhysicalBody>(block, PHYSICALBODY);
            if (phys->_destroyable) {
                return true;
            }
        }
    }
    return false;
}

void Systems::AISystem::execute(World *ref)
{
    auto ai_players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, AI});
    auto blocks = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, WALLCOLLISION});
    auto map = getMap(ref);
    for (const auto &p : ai_players) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(p, PHYSICALBODY);
        auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(p, GRAPHICALBODY);
        auto pos = graphical->node->getPosition();
        auto div = (physical->x) / 2.0f;
        auto round = (int) (truncf(div));
        float new_x;
        new_x = (float) round * 2.0f + (physical->x < 0.f ? -1.0f : 1.0f);
        div = (physical->y) / 2.0f;
        round = (int) (truncf(div));
        float new_y;
        new_y = (float) round * 2.0f + (physical->y < 0.f ? -1.0f : 1.0f);
        auto bombs = ref->getComponentManager().getEntityByComponents({TIMER});
        auto safe = true;
        for (const auto &bomb : bombs) {
            auto bombNode = ref->getComponentManager().getComponent<Components::GraphicalBody>(bomb, GRAPHICALBODY)->node;
            auto bombPos = bombNode->getPosition();
            if ((bombNode->isVisible()) && (isInRange(bombPos.X, bombPos.Y, new_x, new_y) == true)) {
                safe = false;
                break;
            }
        }
        auto aiComponent = ref->getComponentManager().getComponent<Components::AIComponent>(p, AI);
        if (!safe) {
            if (getBlock(ref, new_x - 2, new_y) == 0) {
                aiComponent->action = MOVELEFT;
            } else if (getBlock(ref, new_x + 2, new_y) == 0){
                aiComponent->action = MOVERIGHT;
            } else if (getBlock(ref, new_x, new_y + 2) == 0){
                aiComponent->action = MOVEUP;
            } else {
                aiComponent->action = MOVEDOWN;
            }
        } else {
            bool stable = false;
            auto blocks = std::vector<uint32_t>();
            blocks.push_back(getBlock(ref, new_x - 2, new_y));
            blocks.push_back(getBlock(ref, new_x + 2, new_y));
            blocks.push_back(getBlock(ref, new_x, new_y - 2));
            blocks.push_back(getBlock(ref, new_x, new_y + 2));
            for (const auto &block : blocks) {
                if (block != 0) {
                    auto phys = ref->getComponentManager().getComponent<Components::PhysicalBody>(block, PHYSICALBODY);
                    if (phys->_destroyable) {
                        stable = true;
                        if (myRand(1, 100) <= 5) {
                            aiComponent->action = DROP;
                        }
                    }
                }
            }
            if (!stable) {
                if ((getBlock(ref, new_x - 2, new_y) == 0) && (goodCell(ref, new_x - 2, new_y))) {
                    aiComponent->action = MOVELEFT;
                } else if ((getBlock(ref, new_x + 2, new_y) == 0) && (goodCell(ref, new_x + 2, new_y))){
                    aiComponent->action = MOVERIGHT;
                } else if ((getBlock(ref, new_x, new_y + 2) == 0) && (goodCell(ref, new_x, new_y + 2))){
                    aiComponent->action = MOVEUP;
                } else if ((getBlock(ref, new_x, new_y - 2) == 0) && (goodCell(ref, new_x, new_y - 2))){
                    aiComponent->action = MOVEDOWN;
                } else {
                    aiComponent->action = NONE;
                }
            }


        }
    }
}