/*
** EPITECH PROJECT, 2018
** Project Name
** File description:
** player entity
*/

#ifndef CPP_INDIE_STUDIO_PLAYERENTITY_HPP
#define CPP_INDIE_STUDIO_PLAYERENTITY_HPP

#include "BombEntity.hpp"

class PlayerEntity : public BaseEntity {
	BombEntity &bomb;
public:
	explicit PlayerEntity(EntityPosition &position, BombEntity &bomb) : BaseEntity(position), bomb(bomb) {};
	explicit PlayerEntity(EntityPosition &position);
	bool dropBomb() { return (bomb.drop(position)); };
};

#endif