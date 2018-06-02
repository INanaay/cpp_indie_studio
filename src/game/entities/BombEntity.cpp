/*
** EPITECH PROJECT, 2018
** Project Name
** File description:
** bomb entity
*/

//TODO to remove only for debug
#include <iostream>
#include <thread>

#include "BombEntity.hpp"

//TODO link to graphical events
bool BombEntity::drop(EntityPosition &new_pos)
{
	if (has_been_dropped)
		return (false);
	has_been_dropped = !has_been_dropped;
	position = new_pos;
	std::thread timer([=] {startTimer(); });
	timer.join();
	std::cout << "A bomb has been dropped" << std::endl;
	return (true);
}

//TODO link to graphical events
void BombEntity::startTimer()
{
	std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(2000));
	explode();
}

//TODO link to graphical events && bomb radius on map
void BombEntity::explode()
{
	if (!has_been_dropped)
		return ;
	std::cout << "BOOOOOMMMMM" << std::endl;
	has_been_dropped = !has_been_dropped;
}