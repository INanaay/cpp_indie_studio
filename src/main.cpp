//
// Created by lucas on 30/05/2018.
//

#include <iostream>
#include "Components.hpp"
#include "DemoSystem.hpp"
#include "Entity.hpp"
#include "World.hpp"

int main()
{
    World world;
    Entity *test = world.createEntity();

    world.addSystem<DemoSystem>(uint32_t(99));


    world.update();
}
