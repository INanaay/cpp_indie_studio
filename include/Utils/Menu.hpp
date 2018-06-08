//
// Created by NANAA on 28/05/18.
//

#ifndef IRRLITCHTEST_MENU_HPP
#define IRRLITCHTEST_MENU_HPP


#include <IVideoDriver.h>
#include <IGUIEnvironment.h>
#include <iostream>
#include <IrrlichtDevice.h>
#include "GraphicalEngine.hpp"
#include "MenuEventHandler.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800


class Menu {
private:
	GraphicalEngine &m_engine;
	irr::IrrlichtDevice *m_device;
	irr::video::IVideoDriver *m_driver;
	irr::gui::IGUIEnvironment *m_env;
	irr::gui::IGUISkin *m_skin;
	irr::gui::IGUIFont *m_font;
	MenuEventHandler *m_eventHandler;
	void initGUI();
	void display();
public:
	Menu(GraphicalEngine &engine);
	void clearGUI();
};


#endif //IRRLITCHTEST_MENU_HPP
