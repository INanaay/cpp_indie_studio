/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef CPP_INDIE_STUDIO_ENTITY_HPP
#define CPP_INDIE_STUDIO_ENTITY_HPP

#include <cstdint>
#include <irrlicht.h>

struct EntityPosition
{
	uint32_t x;
	uint32_t y;
	uint32_t z;
};

struct BaseEntity
{
	//CTOR
	explicit BaseEntity(EntityPosition &position) : position(position) {};

	//FIELDS
	EntityPosition position;
};

#endif //CPP_INDIE_STUDIO_ENTITY_HPP
