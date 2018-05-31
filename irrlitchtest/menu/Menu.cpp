//
// Created by NANAA on 28/05/18.
//

#include <irrlicht.h>
#include "Menu.hpp"
#include "MenuEventHandler.hpp"

bool is_running;

Menu::Menu(const std::string &fontpath) : m_fontpath(fontpath)
{
	is_running = true;
	display();
}

void Menu::initGUI()
{
	int x = SCREEN_WIDTH / 4;
	int y = 240;

	m_env->addImage(m_driver->getTexture("menubackground.jpg"), irr::core::position2d<int>(0,0));
	m_env->addImage(m_driver->getTexture("title.png"), irr::core::position2d<int>(0,0));
	m_env->addButton(irr::core::rect<irr::s32>(x , y, x * 3, y + 64), 0, GUI_ID_ONE_PLAYER,
		       L"1 PLAYER", L"Exits Program");
	y += 128;
	m_env->addButton(irr::core::rect<irr::s32>(x, y,x * 3, y + 64), 0, GUI_ID_TWO_PLAYERS,
			 L"2 PLAYER", L"Exits Program");
	y += 128;
	m_env->addButton(irr::core::rect<irr::s32>(x, y, x * 3, y + 64), 0, GUI_ID_QUIT_BUTTON,
			 L"QUIT", L"Exits Program");
}

void Menu::display()
{
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(SCREEN_WIDTH, SCREEN_HEIGHT), 16,
							false, false, false, NULL) ; // switch to receiver
	if (device == 0)
		throw std::exception();
	device->setWindowCaption(L"Bomberman");
	device->setResizable(false);
	m_driver = device->getVideoDriver();
	m_env = device->getGUIEnvironment();
	m_skin = m_env->getSkin();
	m_font = m_env->getFont(m_fontpath.c_str());
	if (m_font)
		m_skin->setFont(m_font);
	else
		m_skin->setFont(m_env->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
	initGUI();
	auto listbox = m_env->addListBox(irr::core::rect<irr::s32>(50, 140, 250, 210));
	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.listbox = listbox;
	MenuEventHandler eventHandler(context);
	device->setEventReceiver(&eventHandler);

	while (device->run() && m_driver && is_running) {
		if (device->isWindowActive()) {
			m_driver->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
			m_env->drawAll();
			m_driver->endScene();
		}
	}
	device->drop();
}
