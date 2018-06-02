//
// Created by NANAA on 28/05/18.
//

#include <irrlicht.h>
#include "Menu.hpp"
#include "MenuEventHandler.hpp"
#include "GraphicalEngine.hpp"

bool is_running;

Menu::Menu(GraphicalEngine &engine) : m_engine(engine)
{
	m_device = engine.getDevice();
	m_driver = engine.getDriver();
	m_env = engine.getGui();

	is_running = true;
	display();
}

void Menu::initGUI()
{
	auto x = SCREEN_WIDTH / 4;
	auto y = 240;

	m_env->addImage(m_driver->getTexture("../src/graphical/menu/resources/menubackground.jpg"), irr::core::position2d<int>(0,0));
	m_env->addImage(m_driver->getTexture("../src/graphical/menu/resources/title2.png"), irr::core::position2d<int>(220,20));
	m_env->addButton(irr::core::rect<irr::s32>(x , y, x * 3, y + 64), 0, GUI_ID_ONE_PLAYER,
		       L"1 PLAYER", L"Exits Program");
	y += 80;
	m_env->addButton(irr::core::rect<irr::s32>(x, y,x * 3, y + 64), 0, GUI_ID_TWO_PLAYERS,
			 L"2 PLAYER", L"Exits Program");
	y += 80;
	m_env->addButton(irr::core::rect<irr::s32>(x, y, x * 3, y + 64), 0, GUI_ID_QUIT_BUTTON,
			 L"QUIT", L"Exits Program");
}

void Menu::clearGUI()
{
	const auto &children = m_env->getRootGUIElement()->getChildren();
	while (!children.empty())
		(*children.getLast())->remove(); // Move to Dtor when deleteing loop
}

void Menu::display() {
	m_device->setWindowCaption(L"Bomberman");
	m_skin = m_env->getSkin();
	m_font = m_env->getFont("bebas.ttf");
	if (m_font)
		m_skin->setFont(m_font);
	else
		m_skin->setFont(m_env->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
	initGUI();
}
