/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

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
	while (m_engine->getDevice()->run()) {
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
    auto driver = m_engine->getDriver();
    auto env = m_engine->getGui();
    while (m_engine->getDevice()->run()) {
        if (m_engine->getDevice()->isWindowActive()) {
            if (!is_running) {
                menu.clearGUI();
            }
            driver->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
            env->drawAll();
            driver->endScene();
        }
    }
}