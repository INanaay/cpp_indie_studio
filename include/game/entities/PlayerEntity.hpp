/*
** EPITECH PROJECT, 2018
** Project Name
** File description:
** player entity
*/

#ifndef CPP_INDIE_STUDIO_PLAYERENTITY_HPP
#define CPP_INDIE_STUDIO_PLAYERENTITY_HPP

#include "GameEntity.hpp"
#include "BombEntity.hpp"

class PlayerEntity : public GameEntity {
	const BombEntity &bomb;
public:
	explicit PlayerEntity(uint64_t id, EntityPosition &position, const BombEntity &bomb) : GameEntity(id, CHARACTER, position), bomb(bomb) {};
	bool dropBomb() { return (bomb.drop(position)); };
};

#endif