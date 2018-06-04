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
    try {
        World world;

        auto player = world.createEntity();
        auto test = world.createEntity();

        world.addEntity(player);

        player.addComponent<Components::PhysicalBody>(uint32_t(20), uint32_t(20), uint32_t(20));
        player.addComponent<Components::Acceleration>(uint32_t(10));

        world.info();

        player.removeComponent(ACCELERATION);

        world.info();

    } catch (...) {
        std::cerr << "An error occured" << std::endl;
        return (84);
    }
}
