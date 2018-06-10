//
// Created by lucas on 30/05/2018.
//

#include <iostream>
#include <Systems/BombSystem.hpp>

#ifdef __linux__
#include <X11/Xlib.h>
#include <Systems/BombSystem.hpp>

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
        GraphicalEngine engine(960, 540);
		World world;
		Map map;
		ControllableEventHandler handler;

		auto ctx = startMenu(engine);
		engine.setHandler(&handler);
		map.load3DMap(world, ctx.nbPlayers);

        world.addSystem<Systems::BombSystem>(&engine);
        world.addSystem<Systems::ControllableSystem>(&engine, handler.getKeyDownArray());
        world.addSystem<Systems::MovementSystem>(&engine, handler.getKeyDownArray());
        world.addSystem<Systems::CollisionSystem>(&engine);
        world.addSystem<Systems::LoaderSystem>(&engine);
        world.addSystem<Systems::AISystem>(&engine, map.getMap());
        engine.getScene()->addCameraSceneNode(0, irr::core::vector3df(0, 0, -30), irr::core::vector3df(0, 0, 0));

        while (engine.isRunning()) {
		    engine.getDriver()->beginScene();
            world.update();
            engine.getScene()->drawAll();
		    engine.getDriver()->endScene();
        }
    } catch (...) {
        return (84);
    }
}
