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
        GraphicalEngine engine(800, 800);

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
