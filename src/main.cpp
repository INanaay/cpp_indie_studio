//
// Created by lucas on 30/05/2018.
//

#include <iostream>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

#include "ControllableEventHandler.hpp"
#include "Systems.hpp"
#include "Components.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "World.hpp"

int main()
{
#ifdef __linux__
	XInitThreads();
#endif

	try {
        World world;
        ControllableEventHandler handler;
        GraphicalEngine engine(500, 500);
	Map map(9);

<<<<<<< Updated upstream
	float ycursor = 0.0;
	for (auto y : map.getMap()) {
		float xcursor = 0.0;
		for (auto x : y) {
			auto entity = world.createEntity();
			world.addEntity(entity);
			if (x == 2)
				entity.addComponent<Components::GraphicalBody>(
					"../ressources/models/cobblestone.b3d", "non");
			if (x == 1)
				entity.addComponent<Components::GraphicalBody>(
					"../ressources/models/wood.b3d", "non");
			float posx = 1.0f * xcursor;
			float posy = 1.0f * ycursor;
			entity.addComponent<Components::PhysicalBody>(
				posx, posy, 0.0f);
			xcursor += 1.0f;
		}
		ycursor += 1.0f;
	}

        world.addSystem<Systems::LoaderSystem>(&engine);
	//world.addSystem<Systems::MovementSystem>(&engine);
=======
        engine.setHandler(&handler);

        auto player = world.createEntity();
        world.addEntity(player);
        player.addComponent<Components::GraphicalBody>("../ressources/models/rere.b3d", "non");
        player.addComponent<Components::PhysicalBody>(0.0f, 0.0f, 0.0f);
	    player.addComponent<Components::Velocity>(0.0001f);

        world.addSystem<Systems::LoaderSystem>(&engine);
	    world.addSystem<Systems::MovementSystem>(&engine);
>>>>>>> Stashed changes
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
