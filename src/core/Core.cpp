/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include "PlayerEntity.hpp"
#include "Core.hpp"
#include "Menu.hpp"
#include "Map.hpp"

/*!
 * \brief Core Constructor, init the engine.
 *
 */

Core::Core()
{
	m_engine = std::make_unique<GraphicalEngine>(1080, 720);
}

/*!
 * \brief This will execute the game and display everything needed
 * \warning This function may throw exception
 */

void Core::play()
{
    while (m_engine->isRunning()) {
		m_engine->getDriver()->beginScene();



		m_engine->getScene()->drawAll();
		m_engine->getDriver()->endScene();
	}
}

/*!
 * \brief This funtion display the menu and will set all needed informations for the game
 * \warning This may throw exception
 */

void Core::menu() {
    Menu menu(*m_engine);
    SAppContext context{m_engine->getDevice(), true, 0};
    MenuEventHandler handler(context);

    m_engine->setHandler(&handler);
    while (m_engine->isRunning()) {
        if (m_engine->getDevice()->isWindowActive()) {
            if (!context.isRunning) {
                menu.clearGUI();
                break;
            }
            m_engine->getDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
            m_engine->getGui()->drawAll();
            m_engine->getDriver()->endScene();
        }
    }
    m_engine->dropHandler();
}