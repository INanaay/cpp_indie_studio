//
// Created by NANAA on 31/05/18.
//

#include <iostream>
#include "MenuEventHandler.hpp"
#include "Menu.hpp"

MenuEventHandler::MenuEventHandler(SAppContext &context) : m_context(context)
{

}


bool MenuEventHandler::OnEvent(const irr::SEvent &event)
	{
	if (event.EventType == irr::EET_GUI_EVENT)
	{
		irr::s32 id = event.GUIEvent.Caller->getID();
		irr::gui::IGUIEnvironment* env = m_context.device->getGUIEnvironment();

		switch(event.GUIEvent.EventType)
		{
			case irr::gui::EGET_BUTTON_CLICKED:
				switch(id)
				{
					case GUI_ID_QUIT_BUTTON:
						m_context.device->closeDevice();
						return true;
					case GUI_ID_ONE_PLAYER:
					std::cout << "one player\n";
						m_context.isMenuRunning = false;
						m_context.nbPlayers = 1;
						return true;
					case  GUI_ID_TWO_PLAYERS:
						std::cout << "Two player\n";
						return true;
					default:
						return false;
				}
				break;

			default:
				break;
		}
	}

	return false;
}

void MenuEventHandler::setM_context(SAppContext &context) {
	MenuEventHandler::m_context = context;
}
