/*
** EPITECH PROJECT, 2018
** Project Name
** File description:
** bomb entity
*/

//TODO to remove only for debug
#include <iostream>

#include "BombEntity.hpp"

//TODO link to graphical events
bool BombEntity::drop(EntityPosition &new_pos)
{
	if (has_been_droped)
		return (false);
	has_been_droped = !has_been_droped;
	position = new_pos;
	timerThread = std::thread(startTimer, &this);
	timerThread.join();
	std::cout << "A bomb has been droped" << std::endl;
	return (true);
}

//TODO link to graphical events
void BombEntity::startTimer(const BombEntity &self)
{
	std::this_thread::sleep_for(2s);
	self.explode();
}

//TODO link to graphical events && bomb radius on map
void BombEntity::explode()
{
	if (!has_been_droped)
		return ;
	std::cout << "BOOOOOMMMMM" << std::endl;
	has_been_droped = !has_been_droped;
}