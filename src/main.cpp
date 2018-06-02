//
// Created by lucas on 30/05/2018.
//

#include <iostream>
#include <Menu.hpp>
#include <MenuEventHandler.hpp>
#include "GraphicalEngine.hpp"


int main()
{


	try {
		GraphicalEngine engine(1080, 720);

		Menu menu(engine);
		auto driver = engine.getDriver();
		auto env = engine.getGui();
		while (engine.getDevice()->run()) {
			if (engine.getDevice()->isWindowActive()) {
				if (!is_running)
				{
					menu.clearGUI();
				}
				driver->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
				env->drawAll();
				driver->endScene();
			}
		}


    } catch (...) {
        return 84;
    }
}
