//
// Created by lucas on 30/05/2018.
//

#include <iostream>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

#include "Systems.hpp"
#include "Components.hpp"
#include "Entity.hpp"
#include "World.hpp"

int main()
{
#ifdef __linux__
	XInitThreads();
#endif

	try {
        World world;
        GraphicalEngine engine(500, 500);


        auto player = world.createEntity();
        world.addEntity(player);
        player.addComponent<Components::GraphicalBody>("../ressources/models/rere.b3d", "non");
        player.addComponent<Components::PhysicalBody>(0.0f, 0.0f, 0.0f);
	player.addComponent<Components::Velocity>(0.0001f);

        world.addSystem<Systems::LoaderSystem>(&engine);
	world.addSystem<Systems::MovementSystem>(&engine);
        world.info();

        engine.getScene()->addCameraSceneNode(0, irr::core::vector3df(0, 10, -10), irr::core::vector3df(0, 5, 0));

        world.startWorkers();
        while (engine.isRunning()) {
            engine.getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
            engine.getScene()->drawAll();
            engine.getDriver()->endScene();
        }

        world.waitWorkers();

    } catch (...) {
        std::cerr << "An error occured" << std::endl;
        return (84);
    }
}
