/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <Core.hpp>
#include <Map.hpp>


//CTOR
Core::Core()
: m_gameRunning(false), m_graphicalRunning(false)
{
	m_engine = std::make_unique<GraphicalEngine>(1080, 720);
}


//PROPERTIES
bool Core::isGameRunning() const
{
	return (m_gameRunning);
}

bool Core::isGraphicalRunning() const
{
	return (m_graphicalRunning);
}


//ACTIONS
void Core::addUserAction(UserAction action)
{
	std::unique_lock<std::mutex> lock(m_actionsLock);
	m_userActions.push(action);
}
UserAction Core::getUserAction()
{
	std::unique_lock<std::mutex> lock(m_actionsLock);
	if (m_userActions.empty())
		return UserAction::NONE;
	auto action = m_userActions.back();
	m_userActions.pop();
	return (action);
}

//INTERNAL FUNCTIONS
void Core::executeUserAction(UserAction action)
{
	// if action == QUIT
	// then

	// if action == PAUSE
	// then

	//....
}
