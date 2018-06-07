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
        GraphicalEngine engine(800, 800);
		Map map(9);


		auto perso = world.createEntity();
		world.addEntity(perso);
        perso.addComponent<Components::GraphicalBody>(
                "../ressources/models/rere.b3d", "../ressources/models/re.png");
        perso.addComponent<Components::PhysicalBody>(2.0f, 2.0f, 0.0f);

        keymap player1_keymaps;

        player1_keymaps.emplace_back(irr::EKEY_CODE::KEY_LEFT, CONTROL_ACTION::MOVELEFT);
        player1_keymaps.emplace_back(irr::EKEY_CODE::KEY_RIGHT, CONTROL_ACTION::MOVERIGHT);
        player1_keymaps.emplace_back(irr::EKEY_CODE::KEY_UP, CONTROL_ACTION::MOVEUP);
        player1_keymaps.emplace_back(irr::EKEY_CODE::KEY_DOWN, CONTROL_ACTION::MOVEDOWN);

        perso.addComponent<Components::Controllable>(player1_keymaps);
        perso.addComponent<Components::Velocity>(0.f);

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
        world.addSystem<Systems::ControllableSystem>(&engine, handler.getKeyDownArray());

        engine.setHandler(&handler);

        world.info();

        auto cam = engine.getScene()->addCameraSceneNode(0, irr::core::vector3df(21, 10,-40), irr::core::vector3df(21,21,21));

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
