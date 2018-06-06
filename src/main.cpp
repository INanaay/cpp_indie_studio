//
// Created by lucas on 30/05/2018.
//

#include <iostream>

#ifdef __linux__
#include <X11/Xlib.h>
#include <Systems/AISystem.hpp>
#include <AI.hpp>

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
        GraphicalEngine engine(800, 800);
		Map map(9);


		auto perso = world.createEntity();
		world.addEntity(perso);
        perso.addComponent<Components::GraphicalBody>(
                "../ressources/models/rere.b3d", "../ressources/models/re.png");
        perso.addComponent<Components::PhysicalBody>(2.0, 2.0, 0.0);
        perso.addComponent<Components::AIComponent>();
		float ycursor = 0.0;
		for (auto y : map.getMap()) {
            float xcursor = 0.0;
            for (auto x : y) {

                if (x == '2') {
                    auto entity = world.createEntity();
                    world.addEntity(entity);
                    entity.addComponent<Components::GraphicalBody>(
                            "../ressources/models/cobblestone.obj", "../ressources/models/cobblestone.png");
                    entity.addComponent<Components::PhysicalBody>(
                            xcursor, ycursor, 0.0f);
                }
                if (x == '1') {
                    auto entity = world.createEntity();
                    world.addEntity(entity);
                    entity.addComponent<Components::GraphicalBody>(
                            "../ressources/models/wood.obj", "../ressources/models/wood.png");
                    entity.addComponent<Components::PhysicalBody>(
                            xcursor, ycursor, 0.0f);
                }
                xcursor += 2.0f;
            }
            ycursor += 2.0f;
        }

        world.addSystem<Systems::LoaderSystem>(&engine);
        world.addSystem<Systems::MovementSystem>(&engine);
        world.addSystem<Systems::AISystem>(&engine);
        world.info();

		engine.setHandler(&handler);
		
        auto cam = engine.getScene()->addCameraSceneNode(0, irr::core::vector3df(21, -15, -30), irr::core::vector3df(21, 21, 0));

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
