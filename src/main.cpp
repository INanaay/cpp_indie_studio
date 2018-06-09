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
#include "Menu.hpp"

SAppContext startMenu(GraphicalEngine &engine)
{
	SAppContext context{engine.getDevice(), true, 0};
	Menu menu(engine);
	MenuEventHandler handler(context);

	engine.setHandler(&handler);
	while (engine.isRunning())
	{
		if (engine.getDevice()->isWindowActive()) {
			if (!context.isRunning) {
				menu.clearGUI();
				break;
			}
		}
		engine.getDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
		engine.getGui()->drawAll();
		engine.getDriver()->endScene();
	}
	engine.dropHandler();
	return context;
}

int main()
{
#ifdef __linux__
	XInitThreads();
#endif

	try {

        GraphicalEngine engine(800, 800);
		World world;
		Map map;
		ControllableEventHandler handler;

		//startMenu(engine);
		engine.setHandler(&handler);
		map.load3DMap(world, 2);
		world.addSystem<Systems::ControllableSystem>(&engine, handler.getKeyDownArray());
		world.addSystem<Systems::MovementSystem>(&engine);
		world.addSystem<Systems::CollisionSystem>(&engine);
		world.addSystem<Systems::LoaderSystem>(&engine);
		engine.getScene()->addCameraSceneNode(0, irr::core::vector3df(0, 0, -40), irr::core::vector3df(0, 0, 0));

        while (engine.isRunning()) {
		engine.getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
		world.update();
		engine.getScene()->drawAll();
		engine.getDriver()->endScene();
        }

    } catch (...) {
        return (84);
    }
}
