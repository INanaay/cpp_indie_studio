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
		startMenu(engine);
		World world;


		world.startWorkers();

        while (engine.isRunning()) {
			engine.getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
            engine.getScene()->drawAll();
            engine.getDriver()->endScene();
        }

        world.waitWorkers();

    } catch (...) {
        return (84);
    }
}
