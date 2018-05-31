/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef INDIESTUDIO_CORE_HPP
#define INDIESTUDIO_CORE_HPP

#include <queue>
#include <thread>
#include <GameManager.hpp>
#include <GraphicalManager.hpp>
#include <entities/UserAction.hpp>
#include <mutex>

class Core
{
public:
	//CTOR
	Core();

	//USER ACTIONS
	void addUserAction(UserAction action);
	UserAction getUserAction();

	//PROPERTIES
	bool isGameRunning() const;
	bool isGraphicalRunning() const;

private:
	//FIELDS
	bool m_gameRunning;
	bool m_graphicalRunning;
	std::mutex m_actionsLock;
	std::thread m_gameThread;
	std::thread m_graphicalThread;
	std::queue<UserAction> m_userActions;
	std::unique_ptr<GameManager> m_gameManager;
	std::unique_ptr<GraphicalManager> m_graphicalManager;

	//FUNCTIONS
	void executeUserAction(UserAction action);
};


#endif //INDIESTUDIO_CORE_HPP
