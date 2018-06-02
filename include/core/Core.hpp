/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef INDIESTUDIO_CORE_HPP
#define INDIESTUDIO_CORE_HPP

#include <mutex>
#include <queue>
#include <thread>
#include "GraphicalEngine.hpp"

class Core
{
public:
	//CTOR
	Core();
	~Core() = default;
	void play();
	void menu();

private:
	//FIELDS

	std::unique_ptr<GraphicalEngine> m_engine;

	//FUNCTIONS
};


#endif //INDIESTUDIO_CORE_HPP
