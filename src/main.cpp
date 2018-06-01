//
// Created by lucas on 30/05/2018.
//

#include <iostream>
#include "GraphicalEngine.hpp"


int main()
{
    try {
        GraphicalEngine engine(1080, 720);
	auto de = engine.getDevice();
	auto dr = engine.getDriver();
	while (de->run())
	{
		dr->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
		dr->endScene();
	}
    } catch (...) {
        return 84;
    }
}
