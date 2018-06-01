/*
** EPITECH PROJECT, 2018
** Project Name
** File description:
** bomb entity
*/

#ifndef CPP_INDIE_STUDIO_BOMBENTITY_HPP
#define CPP_INDIE_STUDIO_BOMBENTITY_HPP

#include <thread>
#include "GameEntity.hpp"

class BombEntity : public GameEntity {
	bool has_been_dropped = false;
	void startTimer();
public:
	explicit BombEntity(uint64_t id, EntityPosition &position) : GameEntity(id, BOMB, position) {};
	bool drop(EntityPosition &new_pos);
	void explode();
};

#endif