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

void Systems::AISystem::execute(World *ref)
{
    auto ai_players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, AI});
    auto blocks = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, WALLCOLLISION});
    auto map = getMap(ref);
    for (const auto &p : ai_players) {
        auto physical = ref->getComponentManager().getComponent<Components::PhysicalBody>(p, PHYSICALBODY);
        auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(p, GRAPHICALBODY);
        auto pos = graphical->node->getPosition();
        auto bombs = ref->getComponentManager().getEntityByComponents({TIMER});
        auto safe = true;
        for (const auto &bomb : bombs) {
            auto bombPos = ref->getComponentManager().getComponent<Components::GraphicalBody>(bomb, GRAPHICALBODY)->node->getPosition();
            if (isInRange(bombPos.X, bombPos.Y, pos.X, pos.Y)) {
                safe = false;
                break;
            }
        }
        auto aiComponent = ref->getComponentManager().getComponent<Components::AIComponent>(p, AI);
        if (!safe) {
            auto div = (physical->x) / 2.0f;
            auto round = (int) (truncf(div));
            float new_x;
            new_x = (float) round * 2.0f + (physical->x < 0.f ? -1.0f : 1.0f);
            div = (physical->y) / 2.0f;
            round = (int) (truncf(div));
            float new_y;
            new_y = (float) round * 2.0f + (physical->y < 0.f ? -1.0f : 1.0f);
        } else {
            auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(p, BOMBMANAGER);
            auto x = myRand(1, 100);
            if (x == 2) {
                aiComponent->action = DROP;
            } else {
                auto div = (physical->x) / 2.0f;
                auto round = (int) (truncf(div));
                float new_x;
                new_x = (float) round * 2.0f + (physical->x < 0.f ? -1.0f : 1.0f);
                div = (physical->y) / 2.0f;
                round = (int) (truncf(div));
                float new_y;
                new_y = (float) round * 2.0f + (physical->y < 0.f ? -1.0f : 1.0f);
                std::cout << "top " << _map[(new_x) / 2 + 8][16 - ((new_y - 1) / 2 + 8)] << std::endl;
                std::cout << "bottom " << _map[(new_x) / 2 + 8][16 - ((new_y + 1) / 2 + 8)] << std::endl;
                std::cout << "left " << _map[(new_x - 1) / 2 + 8][16 - ((new_y) / 2 + 8)] << std::endl;
                std::cout << "right " << _map[(new_x + 1) / 2 + 8][16 - ((new_y) / 2 + 8)] << std::endl;
                if (_map[(new_x - 1)/ 2 + 8][16 - (new_y / 2 + 8)] == '0') {
                    std::cout << "Left" << std::endl;
                    aiComponent->action = MOVELEFT;
                } else if (_map[(new_x + 1) / 2 + 8][16 - (new_y / 2 + 8)] == '0') {
                    std::cout << "Right" << std::endl;
                    aiComponent->action = MOVERIGHT;
                } else if (_map[(new_x) / 2 + 8][16 - ((new_y - 1) / 2 + 8)] == '0') {
                    std::cout << "Up" << std::endl;
                    aiComponent->action = MOVEUP;
                } else if (_map[(new_x) / 2 + 8][16 - ((new_y + 1) / 2 + 8)] == '0') {
                    std::cout << "Down" << std::endl;
                    aiComponent->action = MOVEDOWN;
                } else {
                    //std::cout << "Drop" << std::endl;
                    aiComponent->action = DROP;
                }
                //std::cout << "action = " << aiComponent->action << std::endl;
            }
        }
    }
}