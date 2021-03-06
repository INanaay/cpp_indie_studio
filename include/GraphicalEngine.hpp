//
// Created by lucas on 31/05/2018.
//

#ifndef INDIESTUDIO_GRAPHICALINITIALIZER_H
#define INDIESTUDIO_GRAPHICALINITIALIZER_H

#include <irrlicht.h>
#include <cstdint>
#include <iostream>

using Device = irr::IrrlichtDevice *;
using Driver = irr::video::IVideoDriver *;
using Scene = irr::scene::ISceneManager *;
using Gui = irr::gui::IGUIEnvironment *;
using EventHandler = irr::IEventReceiver *;
using MetaSelector = irr::scene::IMetaTriangleSelector *;

class GraphicalEngine {
public:
	GraphicalEngine(uint32_t x, uint32_t y);
	~GraphicalEngine() noexcept = default;

	bool isRunning() const noexcept { return _device->run(); };
	const Device getDevice() const noexcept { return _device; };
    const Driver getDriver() const noexcept { return _driver; };
    const Scene getScene() const noexcept { return _scene; };
    const Gui getGui() const noexcept { return _gui; };
    const EventHandler getHandler() const noexcept {return _handler;};
    void dropHandler() noexcept  {_handler = nullptr; _device->setEventReceiver(nullptr);}
    void setHandler(EventHandler hand) noexcept {_handler = hand; _device->setEventReceiver(_handler);};
	const MetaSelector getMetaSelector() const noexcept { return _metaSelector;};

private:
	Device _device;
	Driver _driver;
	Scene _scene;
	Gui _gui;
    	EventHandler _handler;
	MetaSelector _metaSelector;
};

#endif //INDIESTUDIO_GRAPHICALINITIALIZER_H
