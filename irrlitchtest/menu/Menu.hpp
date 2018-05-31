//
// Created by NANAA on 28/05/18.
//

#ifndef IRRLITCHTEST_MENU_HPP
#define IRRLITCHTEST_MENU_HPP


#include <IVideoDriver.h>
#include <IGUIEnvironment.h>
#include <iostream>
#include <IrrlichtDevice.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720


class Menu {
private:
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *m_driver;
	irr::gui::IGUIEnvironment *m_env;
	irr::gui::IGUISkin *m_skin;
	irr::gui::IGUIFont *m_font;
	void initGUI();
	void display();
public:
	Menu();
};


#endif //IRRLITCHTEST_MENU_HPP
